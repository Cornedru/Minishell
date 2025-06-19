#!/bin/bash

MINISHELL="./minishell"
LOG="test_log.txt"
TMP_MINISHELL=".tmp_msh"
TMP_BASH=".tmp_bash"

# Tous les tests, organisés par catégorie
tests=(
  # 1. Commandes simples / builtins
  "ls"
  "pwd"
  "echo salut"
  "echo -n salut"
  "echo \"salut les gens\""
  "env"
  "cd .. && pwd"
  "cd && pwd"
  "export VAR=42 && echo \$VAR"
  "unset VAR && echo \$VAR"
  "exit"
  "exit 42"
  "exit salut"

 o
  # 2. Parsing / quotes / variables
  ""
  """"
  "'"
  "echo 'salut les gens'"
  "echo \"salut les gens\""
  "echo 'salut \"\$USER\"'"
  "echo \"salut '\$USER'\""
  "USER=bob && echo \$USER"
  "echo \$USER42"
  "echo \$\$"
  "echo \$HOME/\$USER/test"
  "ls -l"
  "echo ok"
  "echo \"un mot\" \"deuxième mot\""

  # 3. Redirections
  "echo salut > test.txt && cat test.txt"
  "echo ajout >> test.txt && cat test.txt"
  "cat < test.txt"
  "wc -l < test.txt"
  "cat < test.txt | grep salut > output.txt"
  "grep ajout < test.txt | wc -l"

  # 4. Pipes
  "ls | grep minishell"
  "cat test.txt | wc -l"
  "cat test.txt | grep ajout | wc -l"
  "echo hello | tee file.txt > /dev/null"
  "cat < test.txt | grep test > result.txt"

  # 5. Heredoc
  "cat << EOF\\nheredoc test\\nEOF"
  "grep salut << END\\nsalut\\nbonjour\\nEND"

  # 6. Opérateurs logiques (bonus)
  "false || echo OK"
  "true && echo OK"
  "false && echo KO"
  "true || echo KO"

  # 7. Parenthèses (bonus)
  "(echo test)"
  "(cd .. && pwd)"
  "((false || true) && echo OK)"

  # 9. Cas d'erreurs
  "cat fichier_inexistant"
  "> /root/test.txt"
  "cd fichier_non_existant"
  "exit 9999999999999999999"
  "| ls"
  "ls |"
  "echo salut >"
  "cat <<"
  "echo \"salut"

  # 10. Hardcore
  "echo \"salut | ls\" | grep salut"
  "echo 'salut > test.txt' > trash.txt && cat trash.txt"
  "echo \"\$UNDEFVAR\" && echo \$?"
  "ls | | wc"
  "echo \"test\" > | wc"
  "export A=42 && export B=\$A && echo \$B"
  "echo \\\"test\\\""
  "(echo coucou && (echo nested))"
  "cat << END\\nline 1\\nline 2\\nEND"
  "echo \$((5 + 3))"
  "echo | cat | cat | cat | cat | cat"
  "export PATH=toto && ls"
  "echo \\\\\\\"nested quotes\\\\\\\""
  "echo > test.txt | echo coucou >> test.txt && cat test.txt"
)

run_test() {
  local cmd="$1"

  # Heredoc : gestion des retours à la ligne
  if [[ "$cmd" == *"<< "* ]]; then
    printf "%b\n" "$cmd" | $MINISHELL > "$TMP_MINISHELL" 2>&1
    printf "%b\n" "$cmd" | bash        > "$TMP_BASH"     2>&1
  else
    echo "$cmd" | $MINISHELL > "$TMP_MINISHELL" 2>&1
    echo "$cmd" | bash        > "$TMP_BASH"     2>&1
  fi

  diff -q "$TMP_MINISHELL" "$TMP_BASH" > /dev/null
  if [ $? -eq 0 ]; then
    echo -e "[\e[32mOK\e[0m] $cmd" | tee -a "$LOG"
  else
    echo -e "[\e[31mFAIL\e[0m] $cmd" | tee -a "$LOG"
    echo "--- Minishell ---" >> "$LOG"
    cat "$TMP_MINISHELL" >> "$LOG"
    echo "--- Bash ---" >> "$LOG"
    cat "$TMP_BASH" >> "$LOG"
    echo "--------------" >> "$LOG"
  fi
}

# Nettoyage
rm -f "$LOG" "$TMP_MINISHELL" "$TMP_BASH" test.txt output.txt result.txt file.txt trash.txt

echo "=== DÉBUT DES TESTS ===" | tee -a "$LOG"
for t in "${tests[@]}"; do
  run_test "$t"
done
echo "=== FIN DES TESTS ===" | tee -a "$LOG"
