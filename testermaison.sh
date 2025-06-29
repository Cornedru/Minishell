#!/bin/bash

MINISHELL="./minishell"   # chemin vers ton minishell
TEST_FILE="test_commands.sh"
OUTPUT_FILE="minishell_output.txt"

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

# Lancement du minishell avec le fichier en entrée, sortie vers fichier
$MINISHELL < "$TEST_FILE" > "$OUTPUT_FILE" 2>&1

echo "Tests terminés, sortie enregistrée dans $OUTPUT_FILE"
