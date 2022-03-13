int main(void) {
    int a = 1, d = 2, c;
    float x = 1.23, y = 1.23e-10;
    if (a <= d) {
        c = a;
        a = d;
        d = c;
        d = 1.2e13;
    }
    char ch[10] = "ok";
    char x, y = 'a';
    c = a + d;
}