# Build
It was something like this
```
sudo apt install qemu-system-x86
```

# Run 
To run a nuttx exec on an emulated lm3s6965evb:
```
qemu-system-arm -M lm3s6965evb -device loader,file=nuttx -serial mon:stdio -nographic -s

```