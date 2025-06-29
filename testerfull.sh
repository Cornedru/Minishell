#!/bin/bash

MINISHELL="./minishell"   # chemin vers ton minishell
BASH="/bin/bash"

TEST_FILE="test_commands.sh"
MINISHELL_OUTPUT="minishell_output.txt"
BASH_OUTPUT="bash_output.txt"

# Création du fichier de commandes de test
cat > "$TEST_FILE" << EOF
echo Hello World
echo -n No newline
pwd
cd ..
pwd
cd /
pwd
export TEST_VAR=42
echo \$TEST_VAR
unset TEST_VAR
echo \$TEST_VAR
env
ls -l
cat /etc/passwd | grep root
echo \$?
ls > output.txt
cat < output.txt
rm output.txt
echo 'Single quotes \$HOME are literal'
echo "Double quotes \$HOME expand"
echo "Status code \$?"
echo "Testing append redirection" >> output.txt
cat output.txt
rm output.txt
ls | grep minishell
exit
EOF

# Exécuter les deux shells en parallèle
$MINISHELL < "$TEST_FILE" > "$MINISHELL_OUTPUT" 2>&1 &
pid_minishell=$!

$BASH < "$TEST_FILE" > "$BASH_OUTPUT" 2>&1 &
pid_bash=$!

# Attendre la fin des deux processus
wait $pid_minishell
wait $pid_bash

echo "Exécution terminée."

# Comparaison
diff_output=$(diff -u "$BASH_OUTPUT" "$MINISHELL_OUTPUT")

if [ -z "$diff_output" ]; then
  echo "Les sorties sont identiques ! 🎉"
else
  echo "Différences détectées entre bash et minishell :"
  echo "---------------------------------------------"
  echo "$diff_output"
  echo "---------------------------------------------"
fi
