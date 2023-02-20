def fib(i32 num) -> i32 {
    if (x <= 2) {
        return 1;
    } else {
        return fib(num - 1) + fib(num - 2);
    }
}

out = fib(5)

print(out)