# ft_containers

42 school ft_containers project

## Usage

To compile the project:

```bash
make
```

This creates 2 binaries `containers_ft` and `containers_stl`.

### Diff

To run the diff:

```bash
make diff
```

> **Important** the diff command should return at least the speed of execution difference

You can also run the **diff** command directly with the script `./diff.sh`. This allows you to set the number of `cycles`. To avoid waiting too long don't go above 100.

```bash
./diff.sh 25 vector
./diff.sh 50 stack
./diff.sh 75 map
./diff.sh 100 set
./diff.sh 10 # all
```

### Separate Containers

To run separate container diffs:

```bash
make vector
```

```bash
make stack
```

```bash
make map
```

```bash
make set
```

### Intra

To compile and diff the intra `main.cpp`:

```bash
make intra
```