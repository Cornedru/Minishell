echo Hello World
echo -n No newline
pwd
cd ..
pwd
cd /
pwd
export TEST_VAR=42
echo $TEST_VAR
unset TEST_VAR
echo $TEST_VAR
env
ls -l
cat /etc/passwd | grep root
echo $?
ls > output.txt
cat < output.txt
rm output.txt
echo 'Single quotes $HOME are literal'
echo "Double quotes $HOME expand"
echo "Status code $?"
echo "Testing append redirection" >> output.txt
cat output.txt
rm output.txt
ls | grep minishell
exit
