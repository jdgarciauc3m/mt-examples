# Simple treading examples

- **printargs**: Print the arguments of a thread.
- **printmsg**: Print message three times witn one second between messages.
- **racevar**: Show a data race when two threads access a variable.
- **fixracevar**: Show a fixe for data race in racevar example.
- **dynth**: Create a given number of threads and wait for them to finish.
- **dynthalloc**: Create a given number of threads and wait for them to finish. The
  thread ids are crated on dynamic memory.

## IMPORTANT NOTE: Use of Thread Sanitizer

You may get a warning when running the examples with Thread Sanitizer. This 
is due to interactions with ASLR (Address Space Layout Randomization) and the way the
compiler generates code.

```
FATAL: ThreadSanitizer: unexpected memory mapping
```

In such case you can temporarily change the ASLR setting to 0.
```bash
sudo sysctl vm.mmap_rnd_bits=30
```