    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    // Struct yapısı kullanıcı bilgilerini tutmak için kullanılacak
    struct Ogrenci {
        char isim[50];
    };

    // Sezar Şifreleme fonksiyonu
    void sezarSifrele(char metin[], int kaydirma) {
        int i = 0;
        while (metin[i] != '\0') {
            if (metin[i] >= 'A' && metin[i] <= 'Z') {
                metin[i] = ((metin[i] - 'A' + kaydirma) % 26) + 'A';
            } else if (metin[i] >= 'a' && metin[i] <= 'z') {
                metin[i] = ((metin[i] - 'a' + kaydirma) % 26) + 'a';
            }
            i++;
        }
    }

    // Sezar Şifresini çözen fonksiyon
    void sezarCoz(char metin[], int kaydirma) {
        kaydirma = 26 - kaydirma; // Kaydırma tersine çevriliyor
        sezarSifrele(metin, kaydirma);
    }

    // Dosyaya yazma fonksiyonu
    void dosyayaYaz(char metin[], char dosyaAdi[]) {
        FILE *dosya = fopen(dosyaAdi, "w");
        if (dosya == NULL) {
            printf("Dosya acilamadi.\n");
            return;
        }
        fprintf(dosya, "%s", metin);
        fclose(dosya);
    }
    //Dosyaya yazma foksiyonu 2
    void dosyayaYaz2(char metin[], char dosyaAdi[]) {
        FILE *dosya = fopen(dosyaAdi, "w");
        if (dosya == NULL) {
            printf("Dosya acilamadi.\n");
            return;
        }
        fprintf(dosya, "%s", metin);
        fclose(dosya);
    }

    // Dosyadan okuma fonksiyonu
    void dosyadanOku(char metin[], char dosyaAdi[]) {
        FILE *dosya = fopen(dosyaAdi, "r");
        if (dosya == NULL) {
            printf("Dosya acilamadi.\n");
            return;
        }
        fgets(metin, 100, dosya);
        fclose(dosya);
    }

    // En büyük asal çarpanı bulan fonksiyon
    int enBuyukAsalCarpan(int numara) {
        int i, j, flag;
        int enBuyukAsal = 1;

        for (i = 2; i <= numara; i++) {
            if (numara % i == 0) {
                flag = 1;
                for (j = 2; j <= i / 2; j++) {
                    if (i % j == 0) {
                        flag = 0;
                        break;
                    }
                }
                if (flag == 1 && i > enBuyukAsal) {
                    enBuyukAsal = i;
                }
            }
        }
        return enBuyukAsal;
    }

    // Kullanıcıdan öğrenci numarasını ve en büyük asal çarpanı alıp doğruluk kontrolü yapan fonksiyon
    int parolaKontrol(int numara) {
        int parola;
        printf("Ogrenci numaraniz: %d\n", numara);
        printf("En Buyuk Asal Carpan: ");
        scanf("%d", &parola);

        if (parola == enBuyukAsalCarpan(numara)) {
            return 1; // Parola doğru
        } else {
            return 0; // Parola yanlış
        }
    }

    int main() {
        struct Ogrenci ogrenci;

        FILE *dosya;
        char name[50];
        dosya=fopen("ornek.txt","w");
        if(dosya!=NULL)
        {
            printf("Lutfen Adinizi ve Soyadinizi Giriniz:\t  ");
            gets(name);
            strcpy(ogrenci.isim,name);
        }
        else
        {
        printf("Dosya acilamadi.\n");
        return 1;
        }


        int numara;
        printf("Ogrenci numarasi: ");
        scanf("%d", &numara);

        int kaydirma = numara % 10; // Kaydırma miktarı öğrenci numarasının son rakamı
        char sifrelenmisMetin[100];

        // İsimi birleştirip şifreleme işlemi
        sprintf(sifrelenmisMetin, "%s ", ogrenci.isim);
        sezarSifrele(sifrelenmisMetin, kaydirma);
        dosyayaYaz(sifrelenmisMetin, "sifrelimetin.txt");
        dosyayaYaz2(ogrenci.isim,"girilenisimvesoyad.txt");

        if (parolaKontrol(numara)) {
            char sifreliMetin[100];
            dosyadanOku(sifreliMetin, "sifrelimetin.txt");
            printf("Sifreli Metin: %s\n", sifreliMetin);

            sezarCoz(sifreliMetin, kaydirma);
            printf("Cozulmus Metin: %s\n", sifreliMetin);
            printf("Orijinal Metin: %s \n", ogrenci.isim);
        } else {
            printf("Hatali bir parola girdiniz.\n");
        }

        return 0;
    }
