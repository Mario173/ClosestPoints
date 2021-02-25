#include <iostream>

//za funkciju sqrt koja računa korijen
#include <cmath>

//za mjerenje vremena
#include <chrono>

typedef struct{
    double x, y;
} tocka;

//provjera udaljenosti između 2 točke u O(1) operacija
//umjesto ove funkcije može se koristiti funkcija hypot iz zaglavlja cmath
double udaljenost(tocka a, tocka b)
{
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

double bruteForce(tocka *sve, int start, int end)
{
    int i, j;
    double min;
    for(i = start; i < end; i++)
    {
        for(j = i + 1; j <= end; j++)
        {
            double ud = udaljenost(sve[i], sve[j]);
            if(i == start && j == start + 1)
                min = ud;
            else if(ud < min)
                min = ud;
        }
    }
    return min;
}

double min(double x, double y)
{
    if(x < y)
        return x;
    return y;
}

//merge sort --> O(nlogn) --> umjesto ovih funkcija može se koristiti funkcija sort iz zaglavlja algorithm
//Spaja 2 niza
void merge(tocka arr[], int l, int m, int r, int koji)
{
    int n1 = m - l + 1;
    int n2 = r - m;
 
    //Privremena polja
    tocka L[n1], R[n2];
 
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    //Spajamo polja u arr[l...r]
    int i = 0;
    int j = 0;
    int k = l;
 
    if(koji == 0)
    {
        //sortiramo po x koordinati
        while (i < n1 && j < n2) 
        {
            if (L[i].x <= R[j].x) 
            {
                arr[k] = L[i];
                i++;
            }
            else 
            {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
    }
    else
    {
        //sortiramo po y koordinati
        while (i < n1 && j < n2) 
        {
            if (L[i].y <= R[j].y) 
            {
                arr[k] = L[i];
                i++;
            }
            else 
            {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
    }
    
 
    //Ako je ostao neki element u L, ubaci ga
    while (i < n1) 
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    //Ako je ostao neki element u R, ubaci ga
    while (j < n2) 
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(tocka arr[],int l,int r, int koji){
    if(l >= r)
    {
        return;
    }
    int m = (l + r - 1) / 2;
    mergeSort(arr,l,m, koji);
    mergeSort(arr,m + 1,r, koji);
    merge(arr,l,m,r, koji);
}

//pronalazi najmanju udaljenost točaka u pruzi širine 2d oko linije presijecanja
double minPruga(tocka pruga[], int n, double d)
{
    double min = d;
    for(int i = 0; i < n; i++)
    {
        //ova petlja se zavrti najviše 7 puta --> ukupno se obe petlje zavrte najvise 7n puta --> O(n)
        for(int j = i + 1; j < n && (pruga[j].y - pruga[i].y) < min; j++)
        {
            double dist = udaljenost(pruga[i], pruga[j]);
            if(dist < min)
                min = dist;
        }
    }
    return min;
}

//nalaženje najmanje udaljenosti između 2 od n točaka u ravnini u O(nlogn) operacija
double minUdaljenost(tocka x[], tocka y[], int start, int end)
{
    double curr_min;
    if(end - start <= 2)
    {
        //brute-force metoda
        return bruteForce(x, start, end);
    }
    int mid = (start + end) / 2, li = 0, ri = 0;
    tocka midPoint = x[mid];
    tocka yl[mid], yr[end - mid], xl[mid], xr[end - mid];
    for(int i = start; i <= end; i++)
    {
        if(y[i].x <= midPoint.x && li < mid)
        {
            yl[li].x = y[i].x;
            yl[li].y = y[i].y;
            li++;
        }
        else
        {
            yr[ri].x = y[i].x;
            yr[ri].y = y[i].y;
            ri++;
        }
        if(i <= mid)
        {
            xl[i].x = x[i].x;
            xl[i].y = x[i].y;
        }
        else
        {
            xr[i - mid - 1].x = x[i].x;
            xr[i - mid - 1].y = x[i].y;
        } 
    }
    double dl = minUdaljenost(xl, yl, start, mid); //najmanja udaljenost lijevo od linije presijecanja
    double dr = minUdaljenost(xr, yr, mid + 1, end); //najmanja udaljenost desno od linije presijecanja
    //još je preostalo naći minimalnu udaljenost između točaka gdje je jedna lijevo, a druga desno od linije presijecanja
    double d = min(dl, dr);
    tocka pruga[end];
    int j = 0;
    for(int i = start; i <= end; i++)
    {
        if(abs(y[i].x - midPoint.x) < d)
        {
            pruga[j].x = y[i].x;
            pruga[j].y = y[i].y;
            j++;
        }
    }
    return minPruga(pruga, j, d);
}

//unošenje točaka u O(n) operacija --> ukupno O(nlogn)
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
        tocka xt[n], yt[n];
        for(i = 0; i < n; i++)
        {
            double x, y;
            std::cout << "Unesite x koordinatu " << i + 1 << ". tocke: ";
            std::cin >> x;
            xt[i].x = x; //niz tocaka koji ce biti sortiran prema x koordinati
            yt[i].x = x; //niz tocaka koji ce biti sortiran prema y koordinati
            std::cout << "Unesite y koordinatu " << i + 1 << ". tocke: ";
            std::cin >> y;
            xt[i].y = y;
            yt[i].y = y;
        }
        auto start1 = std::chrono::high_resolution_clock::now();
        std::cout << "\nNajmanja udaljenost između unesenih točaka je: " << bruteForce(xt, 0, n - 1) << std::endl; //O(n^2)
        auto end1 = std::chrono::high_resolution_clock::now();
        auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
        std::cout << "Vrijeme potrebno Brute Force metodi u mikrosekundama je: " << duration1.count() << std::endl;
        auto start2 = std::chrono::high_resolution_clock::now();
        mergeSort(xt, 0, n - 1, 0); //sortiranje niza x po x koordinati --> O(nlogn)
        mergeSort(yt, 0, n - 1, 1); //sortiranje niza y po y koordinati --> O(nlogn)
        std::cout << "\nNajmanja udaljenost izmedu unesenih tocaka je: " << minUdaljenost(xt, yt, 0, n - 1) << std::endl; //O(nlogn)
        auto end2 = std::chrono::high_resolution_clock::now();
        auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
        std::cout << "Vrijeme potrebno Divide & Conquer metodi u mikrosekundama je: " << duration2.count() << std::endl;
    }
    return 0;
}