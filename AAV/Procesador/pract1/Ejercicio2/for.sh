for size in 4 8 16 32
do
./m2s -rob_size $size test-args.i386 2>&1 | grep sim.ipc
done

