// C++ program for implementation of KMP pattern searching
// algorithm
#include <bits/stdc++.h>
#include <time.h>
using namespace std;

clock_t awal, akhir;
 
void computeLPSArray(char* pat, int M, int* lps); // C1
 
// Prints occurrences of txt[] in pat[]
void KMPSearch(char* pat, char* txt) // C2
{
    int M = strlen(pat); //C3
    int N = strlen(txt); //C4
 
    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int lps[M]; //C5
 
    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps); //C6
 
    int i = 0; // index for txt[] //C7
    int j = 0; // index for pat[] //C8
    while ((N - i) >= (M - j)) {
        if (pat[j] == txt[i]) {  //n-m+1
            j++; //n-m
            i++; //n-m
        }
 
        if (j == M) {
            printf("Found pattern at index %d ", i - j);
            j = lps[j - 1];
        }
 
        // mismatch after j matches
        else if (i < N && pat[j] != txt[i]) {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
}
 
// Fills lps[] for given pattern pat[0..M-1]
void computeLPSArray(char* pat, int M, int* lps)
{
    // length of the previous longest prefix suffix
    int len = 0;
 
    lps[0] = 0; // lps[0] is always 0
 
    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar
            // to search step.
            if (len != 0) {
                len = lps[len - 1];
 
                // Also, note that we do not increment
                // i here
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}
 
// Driver program to test above function
int main()
{
    //char txt[] = "ABABDABACDABABCABAB";
    char txt[] = "AAAAAAAAAAAAAAAAAAAAAAAAAAA";
    //char pat[] = "ABABCABAB";
    //char pat[] = "ABABAB";
    char pat[] = "BBB";
    //char pat[] = "AAA";
    awal = clock();
    KMPSearch(pat, txt);
    akhir = clock();
    cout << "Waktu yang dibutuhkan: " << double(akhir-awal)/double(CLOCKS_PER_SEC) << " detik" <<endl;
    return 0;
}