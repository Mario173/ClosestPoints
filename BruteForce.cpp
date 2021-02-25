//Neefikasni algoritam --> O(n^2)

#include <iostream>
#include <cmath>

typedef struct{
    double x, y;
} tocka;
tocka uRavnini[1000];

//provjera udaljenosti između 2 točke u O(1) operacija
double udaljenost(tocka a, tocka b)
{
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

//nalaženje najmanje udaljenosti između 2 od n točaka u ravnini u O(n^2) operacija
double minUdaljenost(tocka *sve, int n)
{
    int i, j;
    double min;
    for(i = 0; i < n; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            double ud = udaljenost(sve[i], sve[j]);
            if(i == 0 && j == 1)
                min = ud;
            else if(ud < min)
                min = ud;
        }
    }
    return min;
}

//unošenje točaka u O(n) operacija --> ukupno O(n^2)
int main()
{
    int i, n;
    std::cout << "Koliko tocaka zelite provjeriti?\n";
    std::cin >> n;
    if(n < 2)
    {
        std::cout << "Morate unijeti barem dvije točke." << std::endl;
    }
    else
    {
        for(i = 0; i < n; i++)
        {
            double x, y;
            std::cout << "Unesite x koordinatu " << i + 1 << ". tocke: ";
            std::cin >> x;
            uRavnini[i].x = x;
            std::cout << "Unesite y koordinatu " << i + 1 << ". tocke: ";
            std::cin >> y;
            uRavnini[i].y = y;
        }
        std::cout << "\nNajmanja udaljenost izmedu unesenih tocaka je: " << minUdaljenost(uRavnini, n) << std::endl;
    }
    return 0;
}