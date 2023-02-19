

template <class T>
T relU(T x) {
    return (T)(x > 0 ? x : 0);
}

template <class T>
T relUDeriv(T x) {
    return (T)(x > 0 ? 1 : 0);
}

template <class T>
T leakyRelU(T x, float a = 0.01) {
    return (T)(x > 0 ? x : a * x);
}

template <class T>
T leakyRelUDeriv(T x, float a = 0.01) {
    return (T)(x > 0 ? 1 : a);
}