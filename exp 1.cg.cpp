#include <stdio.h>
#include <ctype.h>
void caesarCipher(char *text, int shift) {
    char ch;
    for (int i = 0; text[i] != '\0'; ++i) {
        ch = text[i];
        if (isalpha(ch)) {
            if (isupper(ch)) {
                text[i] = (ch + shift - 'A') % 26 + 'A';
            }
            else if (islower(ch)) {
                text[i] = (ch + shift - 'a') % 26 + 'a';
            }
        }
    }
}
int main() {
    char text[100];
    int shift;
    printf("Enter a string: ");
    fgets(text, sizeof(text), stdin);
    printf("Enter shift value (1-25): ");
    scanf("%d", &shift);
    caesarCipher(text, shift);
    printf("Encrypted string: %s", text);
    
    return 0;
}

