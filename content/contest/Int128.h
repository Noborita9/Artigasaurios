/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Fast read/print for \_\_int128, since cin/cout and printf
 * don't support it directly. read() parses a signed integer from stdin
 * one character at a time; print() recurses to emit digits in order.
 * Time: O(\log_{10} N) per call.
 * Status: untested
 */
#pragma once
__int128 read() {
    __int128 x=0,f=1;
    char ch=getchar();
    while (ch<'0'||ch>'9') {
        if(ch == '-')f=-1;
        ch=getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x * f;
}
void print(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}
