def foo(i32 a, i32 b) -> i32 {
    int i = 0
    while (i < 10) {
        print(i)
        i = i + 1
        i += 1
    }
    return i
}

def test(){}


string out = food(5, 6)

print(out)

"this is a' string with si'ngle quotes inside '"
'this is a char (wit"h multple chars for some r"eason) with " inside'