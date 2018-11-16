// A simple recursive function:

function factorial(n) {
    if (n == 0) {
        return 1;
    }
    return n * factorial(n - 1);
}
