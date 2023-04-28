#include <stdio.h>
#include <math.h>
#include <ctype.h>
/* I am a comment */
// int main() {
//     printf("Hello World\n");
//     printf("Answer %d\n", 42);
//     printf("Name %s\n", "Sarah");
//     printf("x equals to %.1f, which is less than %d.\n", 3.5, 100);
// }

// int main() {
//     int usf, euf;
//     printf("Enter US Floor:\n");
//     scanf("%d", &usf);
//                                  
//     euf = usf - 1;
//     printf("EU Floor is %d.\n", euf);
// }

// int main() {
//     char name[100];
//     printf("Enter name\n");
//     scanf("%100s", name);
//     printf("Hello %s\n", name);
// }

// int main() {
//     char line[1000];
//     printf("Enter the name\n");
//     scanf("%[^\n]1000s", line);
//     printf("Hello %s, How are you doing? \n", line);
// }

// int main() {
//     char name[1000];
//     printf("Enter your name:\n");
//     fgets(name, 1000, stdin);  //this is gonna read the new line too when you hit enter after entering your name
//     fgets(variable name, length, input src) it reads the whitespaces
// to get rid of the newline char when enter is hit:
//                                                     #include <string.h>
//                                                      name[strlen(name)-1] = '\0';
//     printf("Hello %s How are you doing?\n", name);

// }
// #include <stdio.h>
// int main() {
//     char greet[100] = "Hello World!";
//     printf("%s \n", greet);
// }

/* escape sequences
                    \n newline
                    \t tab
                    "i love \"  this \" ."  quotes
                    \\ backslash
*/ 
//format specifiers
//                  %d digit
//                  %s string
//                  %c char
//                  %f float 
//                  %lf double
//                  %d bool <stdbool.h>
//                  %u unsigned int
//                  %lld long long int

// %.2f decimal precision
// %16.2f minimum field width ( 16 chars total, space between, -16 for left allignment with 16 charspace)


//MATH functions
//  int main() {            
//     double A = sqrt(9);
//     double B = pow(2,4);
//     int C = round(3.14);
//     int D = ceil(3.14);
//     int E = floor(3.99);
//     double F = fabs(-100);
//     double G = log(3);
//     double H = sin(45);
//     double I = cos(45);
//     double J = tan(45);

// }
//third side of a hypotenuse
// int main(){
//     double A, B, C;

//     printf("Enter side A: ");
//     scanf("%lf", &A);

//     printf("Enter side B: ");
//     scanf("%lf", &B);

//     C = sqrt(pow(A,2) + pow(B,2));

//     printf("Side C: %lf \n", C);
// }

// int main(){
//     char grade;
//     printf("Enter a grade: ");
//     scanf("%c", &grade);

//     // if(grade =='A') {
//     //     printf("Perfect!\n");
//     // } else if (grade == 'B'){
//     //     printf("You did good!\n");
//     // } else if (grade == 'C') {
//     //     printf("You did okay!\n");
//     // } else if(grade == 'D'){
//     //     printf("At least it's not an F!\n");
//     // } else if (grade == 'F'){
//     //     printf("YOU FAILED!\n");
//     // } else {
//     //     printf("That's not a valid grade! ");
//     // }

//     switch(grade){
//         case 'A':
//             printf("Perfect\n");
//             break;
//         case 'B':
//             printf("You did good!\n");
//             break;
//         case 'C':
//             printf("You did okay!\n");
//             break;
//         case 'D':
//             printf("At least it's not an F!\n");
//             break;
//         case 'F':
//             printf("You Failed!");
//             break;
//         default:
//             printf("That is not a valid grade alphabet!");
//     }
//     return 0;
// }
int main() {
    char unit;
    float  temp;

    printf("Is the temperature in (F) or (C)?: ");
    scanf("%c", &unit);
    unit  = toupper(unit);

    if(unit == 'C'){
        printf("Enter the temperature in Celsius: ");
        scanf("%f", &temp);
        temp = (temp*9/5) + 32;
        printf("The temperature in Fahrenheit is: %.1f\n", temp);
    } else if (unit == 'F'){
        printf("Enter the temperature in Fahrenheit: ");
        scanf("%f", &temp);
        temp = ((temp - 32) * 5) / 9;
        printf("The temperature in Celsius is: %.1f\n", temp);
    } else {
        printf("%c is not a valid unit of Temperature!\n", unit);
    }
}
