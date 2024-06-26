#include <iostream>
#include "SuffixTree.cpp"

using namespace std;


int main()
{
    //             0123456789012
    SuffixTree t1("bananabanaba$");

    t1.search("ana"); // Prints: 1 3 7
    t1.search("naba"); // Prints: 4 8
    t1.search("bananabanaba"); // Prints: 0
    t1.search("anx"); // Prints: Not Found

    cout << "=========================\n";
    //             01234567
    SuffixTree t2("AAAAAAA$");
    t2.search("A"); // Prints: 0 1 2 3 4 5 6
    t2.search("AA"); // Prints: 0 1 2 3 4 5
    t2.search("AAX"); // Prints: Not Found

    cout << "=========================\n";
    //             012345678901
    SuffixTree t3("MISSISSIPPI$");
    t3.search("SS"); // Prints: 2 5
    t3.search("S"); // Prints: 2 3 5 6
    t3.search("MISSISSIPPI"); // Prints: 0
    t3.search("SSISS"); // Prints: 2

    cout << "=========================\n";
    //             012345678901
    SuffixTree t4("ABRACADABRA$");
    t4.search("ABRA"); // Prints: 0 7
    t4.search("CADABRA"); // Prints: 4
    t4.search("DABRA"); // Prints: 6
    t4.search("DABRAX"); // Prints: Not Found
    t4.search("A"); // Prints: 0 3 5 7 10

    cout << "=========================\n";
    //             01234567
    SuffixTree t5("RATATAT$");
    t5.search("RAT"); // Prints: 0
    t5.search("AT"); // Prints: 1 3 5
    t5.search("TAT"); // Prints: 2 4
    t5.search("X"); // Prints: Not Found

    cout << "=========================\n";
    //             012345
    SuffixTree t6("ABCDE$");
    t6.search("A"); // Prints: 0
    t6.search("B"); // Prints: 1
    t6.search("E"); // Prints: 4
    t6.search("ABCDE"); // Prints: 0
    t6.search("R"); // Prints: Not Found

    cout << "=========================\n";
    //             012345678
    SuffixTree t7("GATAGACA$");
    t7.search("GA"); // Prints: 0 4
    t7.search("GAC"); // Prints: 4
    t7.search("GAT"); // Prints: 0
    t7.search("A"); // Prints: 1 3 5 7

    cout << "=========================\n";
    //             0123456
    SuffixTree t8("AABBCC$");
    t8.search("A"); // Prints: 0 1
    t8.search("B"); // Prints: 2 3
    t8.search("C"); // Prints: 4 5
    t8.search("ABBC"); // Prints: 1

    cout << "=========================\n";
    //             0123456
    SuffixTree t9("BANANA$");
    t9.search("BAN"); // Prints: 0
    t9.search("AN");  // Prints: 1 3
    t9.search("ANA"); // Prints: 1 3
    t9.search("ANAAA"); // Prints: Not Found
    t9.search("ANANA"); // Prints: 1

    cout << "=========================\n";
    //              012345678901
    SuffixTree t10("AABCCRTARRG$");
    t10.search("A"); // Prints: 0 1 7
    t10.search("AAB"); // Prints: 0
    t10.search("AAR"); // Prints: Not Found
    t10.search("G"); // Prints: 10
    t10.search("R"); // Prints: 5 8 9
    t10.search("RR"); // Prints: 8
    t10.search("RT"); // Prints: 5

    return 0;

}