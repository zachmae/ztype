/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** test
*/

#include <stdio.h>


int main() {
    int zeros = 6;
    int power = 0;
    double nb = 50.f;
    printf("%e\n", nb);

    while (nb < 1 || nb >= 10) {
    	if (nb < 1) {
            nb *= 10;
            power++;
    		//action
    	}
    	if (nb >= 10) {
    		//action2
    	}
    }

    printf("%f", nb);
    for (int i = 0; i < zeros; ++i)
        printf("0");
    printf( (power >= 10 ) ? "e+%i\n" : "e+0%i\n", power);

    //pipe
    printf("pipe(1|4|3) %i\n", 1 | 4 | 3);
    //double pipe
}

//----- operator -----//

//https://learn.microsoft.com/fr-fr/cpp/cpp/binary-operators?view=msvc-170

//----- ----- operator binaire ----- -----//

//----- pipe -----//

//int
/*
octet4   octet3   octet2   octet1
00000000 00000000 00000000 00000001   1
-------- -------- -------- --------

|

octet4   octet3   octet2   octet1
00000000 00000000 00000000 0000100    4
-------- -------- -------- -------

|

octet4   octet3   octet2   octet1
00000000 00000000 00000000 0000011    3
-------- -------- -------- -------


=

octet4   octet3   octet2   octet1
00000000 00000000 00000000 0000111    7
-------- -------- -------- ----421
*/

//----- radix sort -----//

//octet4   octet3   octet2   octet1
//00000000 00000000 00000000 00000001
//-------- -------- -------- --------

//octet4   octet3   octet2   octet1
//00000000 00000000 00000000 00101000 1
//-------- -------- -------- --^-----
//                             1
//octet4   octet3   octet2   octet1
//00000000 00000000 00000000 00001000 3
//-------- -------- -------- ----^---
//                               3

//octet4   octet3   octet2   octet1
//00000000 00000000 00000000 00011000 2
//-------- -------- -------- ---^----
//                              2

//1 << 2

//octet4   octet3   octet2   octet1
//00000000 00000000 00000000 00000100 4position
//-------- -------- -------- -----^--
//                                4
//----- printf %e -----//

//0.5 * 10⁰
//x10 | +1
//5.0 * 10¹ = 50

//----- Enum + pipe + bitshift -----//

//enum day{
//    BONJOUR = 1 << 3 | 1 << 2,
//    AUREVOIR
//};