#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// Fungsi untuk menghitung nilai fungsi f(x)
double fungsi(double x) {
    return exp(x);
}

// Metode Simpson 1/3 untuk perhitungan integral numerik satu pias
double simpson13_single(double a, double b) {
    double c = (a + b) / 2.0;
    double A = (b - a) / 6.0 * (fungsi(a) + 4 * fungsi(c) + fungsi(b));
    return A;
}

// Metode Simpson 1/3 untuk perhitungan integral numerik banyak pias
double simpson13_multiple(double a, double b, int n) {
    double delta_x = (b - a) / n;
    double result = 0.0;

    // Menghitung bagian pertama dan terakhir
    result += fungsi(a) + fungsi(b);

    // Menghitung bagian dengan koefisien 4
    for (int i = 1; i < n; i += 2) {
        result += 4 * fungsi(a + i * delta_x);
    }

    // Menghitung bagian dengan koefisien 2
    for (int i = 2; i < n - 1; i += 2) {
        result += 2 * fungsi(a + i * delta_x);
    }

    // Mengalikan dengan ?x/3
    result *= delta_x / 3.0;

    return result;
}

// Metode Simpson 3/8 untuk perhitungan integral numerik satu pias
double simpson38(double a, double b, double fa, double fx1, double fx2, double fb) {
    double delta_x = (b - a) / 3;
    double result = (3 * delta_x / 8) * (fa + 3 * fx1 + 3 * fx2 + fb);
    
    // Menampilkan header tabel
    cout << "******************************************************" << endl;
    cout << setw(2) << "NO" << setw(20) << "Xi" << setw(30) << "f(Xi)" << endl;
    cout << "******************************************************" << endl;

    // Menampilkan nilai fungsi untuk setiap titik yang diperlukan
    for (int i = 0; i <= 3; ++i) {
        double x = a + i * delta_x;
        cout << "\t" << i;
        cout << setw(20) << x;
        cout << setw(25) << fungsi(x);
        cout << endl;
    }

    return result;
}

int main() {
    // Nilai batas integral
    double a, b;

    // Jumlah pias (untuk metode banyak pias)
    int n;

    // Pilihan metode
    int metode;
    cout << "Masukkan batas bawah (a): ";
    cin >> a;
    cout << "Masukkan batas atas (b): ";
    cin >> b;
    cout << "Masukkan jumlah subinterval (n): ";
    cin >> n;

    cout << "Pilih metode Simpson:\n";
    cout << "1. Metode Simpson (1/3) Satu Pias\n";
    cout << "2. Metode Simpson (1/3) Banyak Pias\n";
    cout << "3. Metode Simpson (3/8)\n";
    cout << "Masukkan pilihan (1, 2, atau 3): ";
    cin >> metode;

    // Menghitung nilai integral sesuai dengan pilihan metode
    double hasilIntegral;
    if (metode == 1) {
        hasilIntegral = simpson13_single(a, b);
    } else if (metode == 2) {
        hasilIntegral = simpson13_multiple(a, b, n);
    } else if (metode == 3) {
        // Hitung nilai fungsi pada titik-titik yang diperlukan
        double fa = fungsi(a);
        double fb = fungsi(b);
        double fx1 = fungsi(a + (b - a) / 3);
        double fx2 = fungsi(a + 2 * (b - a) / 3);

        // Hitung integral menggunakan metode Simpson 3/8 satu pias
        hasilIntegral = simpson38(a, b, fa, fx1, fx2, fb);
    } else {
        cout << "Pilihan tidak valid.\n";
        return 1; // Keluar dengan kode kesalahan
    }

    // Menghitung dan menampilkan galat relatif dalam bentuk persen
    double trueValue = exp(b) - exp(a);
    double galatRelatif = std::abs((trueValue - hasilIntegral) / trueValue) * 100.0;

    // Menampilkan hasil
    cout.precision(5);
    if (metode == 1) {
        cout << "Hasil integral e^x dx dari " << a << " hingga " << b << " dengan metode Simpson 1/3 satu pias" << endl;
		cout << "f(c) = f(" << (a + b) / 2.0 << ") = e^" << (a + b) / 2.0 << " = " << fungsi((a + b) / 2.0) << endl;
    } else if (metode == 2) {
        cout << "Hasil integral ?_" << a << "^" << b << "?e^x dx dengan metode Simpson 1/3 (n = " << n << " pias)" << endl;
    } else {
        cout << "Hasil integral e^x dx dari " << a << " hingga " << b << " dengan metode Simpson 3/8 satu pias" << endl;
    }
    cout << "f(a) = f(" << a << ") = e^" << a << " = " << fungsi(a) << endl;
    cout << "f(b) = f(" << b << ") = e^" << b << " = " << fungsi(b) << endl;
    if (metode == 2) {
        for (int i = 1; i <= n - 1; ++i) {
            double xi = a + i * (b - a) / n;
            cout << "f(x" << i << ") = f(" << xi << ") = e^" << xi << " = " << fungsi(xi) << endl;
        }
    } else if (metode == 3) {
        double x1 = a + (b - a) / 3;
        double x2 = a + 2 * (b - a) / 3;
        cout << "f(x1) = f(" << x1 << ") = e^" << x1 << " = " << fungsi(x1) << endl;
        cout << "f(x2) = f(" << x2 << ") = e^" << x2 << " = " << fungsi(x2) << endl;
    }
    cout << "Hasil Integral Numerik Simpson: " << hasilIntegral << endl;
    cout << "Nilai Sebenarnya: " << trueValue << endl;
    cout << "Galat Relatif: " << galatRelatif << "%" << endl;

    return 0;
}

