tempfile=$(mktemp)
./m2s test-args.i386 > /dev/null 2> $tempfile
line=$(cat $tempfile | grep sim.ipc)
ipc=$(echo $line | awk '{print $2}')
echo "El IPC es $ipc"
rm -f $tempfile
