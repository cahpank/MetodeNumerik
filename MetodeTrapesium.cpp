#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double f(double x) {
    return pow(x, 2) + (4 * x) + 4;
}

double f_prime(double x) {
    return (2 * x) + 4;
}

double rumus_nilai_eksak(double x) {
    return (1.0/3.0) * pow(x, 3) + 2 * pow(x, 2) + 4 * x;
}

double trapesium_satu_pias(double a, double b) {
    double h = b - a;
    double result = h * (f(a) + f(b)) / 2;
    return result;
}

double trapesium_banyak_pias(double a, double b, int n) {
    double delta_x = (b - a) / n;
    double sum = 0.0;
    for (int i = 1; i < n; ++i) {
        double xi = a + i * delta_x;
        sum += f(xi);
    }
    double result = (delta_x / 2) * (f(a) + 2 * sum + f(b));
    return result;
}

double trapesium_banyak_pias_dengan_koreksi_ujung(double a, double b, int n) {
    double delta_x = (b - a) / n;
    double sum = 0.0;

    for (int i = 1; i < n; ++i) {
        double xi = a + i * delta_x;
        sum += f(xi);
    }

    double integral_result = (delta_x / 2) * (f(a) + 2 * sum + f(b));

    // Koreksi ujung
    double delta_x_squared = pow(delta_x, 2);
    double correction_term = (delta_x_squared / 12) * (f_prime(b) - f_prime(a));

    return integral_result - correction_term;
}

int main() {
    double a, b;
    int n;

    cout << "\nMasukkan batas bawah integral: ";
    cin >> a;
    cout << "Masukkan batas atas integral: ";
    cin >> b;
    cout << "Masukkan jumlah iterasi: ";
    cin >> n;

     double nilai_eksak = rumus_nilai_eksak(b) - rumus_nilai_eksak(a);

    double integral_numerik_satu_pias = trapesium_satu_pias(a, b);
    double integral_numerik_banyak_pias = trapesium_banyak_pias(a, b, n);
    double integral_numerik_banyak_pias_koreksi_ujung = trapesium_banyak_pias_dengan_koreksi_ujung(a, b, n);

    double nilai_galat_relatif_satu_pias = abs(nilai_eksak - integral_numerik_satu_pias) / abs(nilai_eksak) * 100;
    double nilai_galat_relatif_banyak_pias = abs(nilai_eksak - integral_numerik_banyak_pias) / abs(nilai_eksak) * 100;
    double nilai_galat_relatif_banyak_pias_koreksi_ujung = abs(nilai_eksak - integral_numerik_banyak_pias_koreksi_ujung) / abs(nilai_eksak) * 100;

    cout << "\nHasil Nilai eksak: " << nilai_eksak << endl;
    cout << "\n-------------------------Pilihan Metode Integral------------------------" << endl;
    cout << "\n1. Metode Trapesium Satu Pias\n";
    cout << "2. Metode Trapesium Banyak Pias\n";
    cout << "3. Metode Trapesium Banyak Pias dengan Koreksi Ujung\n";
    cout << "\nPilih metode integral (1/2/3): ";

    int metode;
    cin >> metode;

    switch (metode) {
        case 1:
            cout << "\n-------------------------Trapesium satu Pias-------------------------" << endl;
            cout << "\nHasil integral numerik: " << fixed << setprecision(4) << integral_numerik_satu_pias << endl;
            cout << "Nilai Galat relatif: " << fixed << setprecision(2) << nilai_galat_relatif_satu_pias << "%" << endl;
            cout << "\n---------------------------------END---------------------------------\n" << endl;
            break;

        case 2:
            cout << "\n------------------------Trapesium Banyak Pias------------------------" << endl;

            // Menampilkan hasil titik pada sumbu x
            cout << "\nf(x" << a << ") = " << f(a) << endl;
            for (int i = 1; i < n; ++i) {
                double xi = i * ((b - a) / n);
                cout << "f(x" << i << ") = " << f(xi) * 2 << endl;
            }
            cout << "f(x" << n << ") = " << f(b) << endl;

            cout << "\nHasil integral numerik: " << fixed << setprecision(6) << integral_numerik_banyak_pias << endl;
            cout << "Nilai Galat relatif: " << fixed << setprecision(1) << nilai_galat_relatif_banyak_pias << "%" << endl;
            cout << "\n---------------------------------END---------------------------------\n" << endl;
            break;

        case 3:
            cout << "\n-------------Trapesium Banyak Pias dengan Koreksi Ujung--------------" << endl;
            
            cout << "\nf(x" << a << ") = " << f_prime(a) << endl;
            for (int i = 1; i < n; ++i) {
                double xi = i * ((b - a) / n);
                cout << "f(x" << i << ") = " << f_prime(xi) * 2 << endl;
            }
            cout << "f(x" << n << ") = " << f_prime(b) << endl;

            cout << "\nHasil integral numerik: " << fixed << setprecision(6) << integral_numerik_banyak_pias_koreksi_ujung << endl;
            cout << "Nilai Galat relatif: " << fixed << setprecision(2) << nilai_galat_relatif_banyak_pias_koreksi_ujung << "%" << endl;
            cout << "\n---------------------------------END---------------------------------\n" << endl;
            break;

        default:
            cout << "Pilihan tidak valid." << endl;
    }

    system("pause");

    return 0;
}
