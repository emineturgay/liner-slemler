#include <iostream>

using namespace std;

#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include<conio.h>
#include<cstring>
using namespace std;

FILE *dosya;
FILE *dosyaa;
FILE *dosya2;
FILE *dosya3;
FILE *dosya4;
FILE *dosya5;
FILE *dosya6;



void bolen_ayrik();
void bolen_lineer(__int64 okunmus_dizi[500]);
void katlama_lineer_yoklama(__int64 okunmus_dizi[500]);
void katlama_ayrik_tasma(__int64 okunmus_dizii[500]);
void kare_ort_lineer(__int64 okunmus_dizi[500]);
void kare_ort_ayrik(__int64 okunmus_dizi[500]);

//ARAMA FONKSÝYONLARI
void random_dosya_ara(int aranan);
void bolen_lineer_bul(int degisken);
void bolen_ayrik_bul(int aranan);
void katlama_lineer_bul(int aranan);
void katlama_ayrik_bul(int aranan);
void kare_ort_lineer_bul(__int64 aranan);
void kare_ort_ayrik_bul(__int64 aranan);

void maliyet_hesapla();
int sayi;
char ad[5];
char soy[5];
__int64 okunan_dizi[500];

char *a;
char *b;
int hash_okunan[500];
int z;
int deger=0;

int x;




struct lineer
{
    __int64 adres;
    char* adi;
    char *soyadi;
    int indeks;
    char okunan_isim[5];//dosyadan okuduðumuz adý tutmak için
    char okunan_soyisim[5];//dosyadan okuduðumuz soyadý saklamak için
};

struct lineer *adres_dizisi[500];
struct lineer *bolen_ayrikk[200000];
struct lineer *katlama_lineer[500];
struct lineer *katlama_ayrik[200000];
struct lineer *kare_lineer[500];
struct lineer *kare_ayrik[2000];
struct lineer *dosya_okuyucu[500];
struct lineer *ptr[500];//bunu baðýl dosyalara isism yazdýrýken kullandýk

int maliyet[7];

int main()
{

    char ogr_ad[5];
    char ogr_soyad[5];

    dosya = fopen("random.txt", "w");


    srand((unsigned)time(NULL));

    int dizi[500];

    for (int i = 0; i < 500; i++)
    {
        dizi[i] = rand() % 1000000000 + 100000000;
        //cout << "dizinin i+1. elemani : " << dizi[i] << endl;

        for (int j = 0; j < i; j++)
        {

            while (dizi[j] == dizi[i])
            {
                //cout << "ayni sayi uretildi : " << endl;
                dizi[i] = rand() % 1000000000 + 100000000;
                //cout << "dizinin i+1. elemaninin yeni degeri : " << dizi[i] << endl;

            }
        }
    }

    int isim[500][5];

    for (int i = 0; i < 500; i++)
    {

        for (int k = 0; k < 5; k++)
        {
            isim[i][k] = rand() % 26 + 0;

        }


    }

    //cout << endl << endl;

    int soyad[500][5];

    for (int i = 0; i < 500; i++)
    {

        for (int k = 0; k < 5; k++)
        {
            soyad[i][k] = rand() % 25 + 0;
            //printf("%c", 'B' + isim[i][k]);
        }

    }

    for (int i = 0; i < 500; i++)
    {

        fprintf(dosya, "%d  ", dizi[i]);
        int k;

        for (k = 0; k < 5; k++)
        {
            fprintf(dosya, "%c", 'A' + isim[i][k]);


        }

        fprintf(dosya, " ");
        for (k = 0; k < 5; k++)
        {
            fprintf(dosya, "%c", 'B' + soyad[i][k]);
        }



        fprintf(dosya, "\n");

    }

    fclose(dosya);





    dosya = fopen("random.txt", "r+");

    int i = 0;
    while (!feof(dosya))
    {
        dosya_okuyucu[i]=new struct lineer;
        ptr[i]=new struct lineer;
        fscanf(dosya, "%d %s %s ", &sayi, ogr_ad, ogr_soyad);
        okunan_dizi[i] = sayi;
        strcpy(dosya_okuyucu[i]->okunan_isim,ogr_ad);
        strcpy(ptr[i]->okunan_isim,ogr_ad);
        strcpy(dosya_okuyucu[i]->okunan_soyisim,ogr_soyad);

        i++;


    }

    fclose(dosya);

    bolen_lineer(okunan_dizi);
    bolen_ayrik();

    katlama_lineer_yoklama(okunan_dizi);
    katlama_ayrik_tasma(okunan_dizi);

    kare_ort_lineer(okunan_dizi);
    kare_ort_ayrik(okunan_dizi);

    for(int i=0; i<500; i++)
    {
        free(dosya_okuyucu[i]);

    }
    int aranacak_sayi;



    cout<<"ARADIGINIZ OGRENCININ OKUL NUMARASINI GIRIN : "<<endl;
    cin>>aranacak_sayi;
    cout<<endl;
    cout<<"RANDOM DOSYA :"<<endl;
    random_dosya_ara(aranacak_sayi);
    cout<<endl<<endl;

    cout<<"BOLEN-KALAN-LINEER YOKLAMA : "<<endl;
    bolen_lineer_bul(aranacak_sayi);
    cout<<endl<<endl;

    cout<<"BOLEN-KALAN-AYRIK TASMA : "<<endl;
    bolen_ayrik_bul(aranacak_sayi);
    cout<<endl<<endl;

    cout<<"KATLAMA-LINEER YOKLAMA : "<<endl;
    katlama_lineer_bul(aranacak_sayi);
    cout<<endl<<endl;

    cout<<"KATLAMA-AYRIK TASMA : "<<endl;
    katlama_ayrik_bul(aranacak_sayi);
    cout<<endl<<endl;

    cout<<"KARE ORTASI LINEER YOKLAMA : "<<endl;
    kare_ort_lineer_bul(aranacak_sayi);
    cout<<endl<<endl;

    cout<<"KARE ORTASI AYRIK TASMA : "<<endl;
    kare_ort_ayrik_bul(aranacak_sayi);
    cout<<endl<<endl;

    maliyet_hesapla();
    system("pause");
    return 0;
}







void bolen_lineer(__int64 okunmus_dizi[500])
{
    int indis;

    dosyaa=fopen("bolen_lineer.txt","w+");
    for (int i = 0; i < 500; i++)
    {

        indis = okunmus_dizi[i] % 500;

        if (adres_dizisi[indis]== NULL)
        {

            adres_dizisi [indis]= new struct lineer;
            adres_dizisi[indis]->adres = okunmus_dizi[i];
            adres_dizisi[indis]->adi=ptr[i]->okunan_isim;
            adres_dizisi[indis]->soyadi=dosya_okuyucu[i]->okunan_soyisim;
            adres_dizisi[indis]->indeks=indis;

        }

        else
        {

            do
            {
                indis = (indis + 1)%500;


            }
            while (adres_dizisi[indis]!= NULL);
            adres_dizisi [indis]= new struct lineer;
            adres_dizisi[indis]->adres = okunmus_dizi[i];
            adres_dizisi[indis]->indeks=indis;
            adres_dizisi[indis]->adi=ptr[i]->okunan_isim;
            adres_dizisi[indis]->soyadi=dosya_okuyucu[i]->okunan_soyisim;

        }



    }

    for(int i=0; i<500; i++)
    {

        if(adres_dizisi[i]==NULL)
        {
            fprintf(dosyaa,"\n");
        }

        fprintf(dosyaa, "%d %s %s\n",adres_dizisi[i]->adres, adres_dizisi[i]->adi, adres_dizisi[i]->soyadi);

    }

    fclose(dosyaa);


}


void bolen_ayrik()
{

    int sayici=0;
    dosya2=fopen("bolen_ayrik.txt","w+");

    for (int i = 0; i < 500; i++)
    {

        x = okunan_dizi[i] % 500;

        if (bolen_ayrikk[x]== NULL)
        {

            bolen_ayrikk [x]= new struct lineer;
            bolen_ayrikk[x]->adres = okunan_dizi[i];
            bolen_ayrikk[x]->adi=ptr[i]->okunan_isim;
            bolen_ayrikk[x]->soyadi=dosya_okuyucu[i]->okunan_soyisim;
            bolen_ayrikk[x]->indeks=x;

        }

        else
        {

            sayici=0;
            do
            {
                x = ((x)%500)+(sayici+500);
                sayici++;


            }
            while (bolen_ayrikk[x]!= NULL);
            bolen_ayrikk[x]= new struct lineer;
            bolen_ayrikk[x]->adres = okunan_dizi[i];
            bolen_ayrikk[x]->indeks=x;

            bolen_ayrikk[x]->adi=ptr[i]->okunan_isim;
            bolen_ayrikk[x]->soyadi=dosya_okuyucu[i]->okunan_soyisim;
        }




    }




    int i=0;

    for(i=0; i<2000; i++)
    {
        if(bolen_ayrikk[i]==NULL)
        {
            fprintf(dosya2,"                     \n");
        }
        else
        {
            fprintf(dosya2, "%d %s %s\n",bolen_ayrikk[i]->adres, bolen_ayrikk[i]->adi, bolen_ayrikk[i]->soyadi);

        }
    }

    fclose(dosya2);
}




void katlama_lineer_yoklama(__int64 okunmus_dizi[500])
{

    dosya3=fopen("katlama_lineer.txt","w");
    int sayi[500][9];
    int sayi1;
    int sayi2;
    int sayi3;
    int ind;
    int onk=10;
    int z=0;
    int toplam;
    for(int i=0; i<500; i++)
    {
        onk=10;
        sayi[i][0]=(okunmus_dizi[i]%10);

        for(int j=1; j<9; j++)
        {
            sayi[i][j]=(okunmus_dizi[i]/onk)%10;
            onk=onk*10;
        }
    }






    for(int i=0; i<500; i++)
    {
        toplam=0;
        sayi1=sayi[i][0]+sayi[i][1]*10+sayi[i][2]*100;
        sayi2=sayi[i][5]+sayi[i][4]*10+sayi[i][3]*100;
        sayi3=sayi[i][6]+sayi[i][7]*10+sayi[i][8]*100;



        toplam=sayi1+sayi2+sayi3;

        ind = toplam % 500;

        if (katlama_lineer[ind]== NULL)
        {

            katlama_lineer [ind]= new struct lineer;
            katlama_lineer[ind]->adres = okunmus_dizi[i];
            katlama_lineer[ind]->adi=ptr[i]->okunan_isim;
            katlama_lineer[ind]->soyadi=dosya_okuyucu[i]->okunan_soyisim;
            katlama_lineer[ind]->indeks=ind;

        }

        else
        {

            do
            {
                ind = (ind+ 1)%500;


            }
            while (katlama_lineer[ind]!= NULL);
            katlama_lineer[ind]= new struct lineer;
            katlama_lineer[ind]->adres = okunmus_dizi[i];
            katlama_lineer[ind]->indeks=ind;
            katlama_lineer[ind]->adi=ptr[i]->okunan_isim;
            katlama_lineer[ind]->soyadi=dosya_okuyucu[i]->okunan_soyisim;

        }




    }

    for(int i=0; i<500; i++)
    {
        fprintf(dosya3, "%d %s %s\n", katlama_lineer[i]->adres, katlama_lineer[i]->adi, katlama_lineer[i]->soyadi);
    }
    fclose(dosya3);
}




void katlama_ayrik_tasma(__int64 okunmus_dizii[500])
{

    dosya4=fopen("katlama_ayrik_tasma.txt","w");


    int sayi[500][9];
    int sayi1;
    int sayi2;
    int sayi3;
    int ind;
    int onk=10;
    int z=0;
    int toplam;
    for(int i=0; i<500; i++)
    {
        onk=10;
        sayi[i][0]=(okunmus_dizii[i]%10);

        for(int j=1; j<9; j++)
        {
            sayi[i][j]=(okunmus_dizii[i]/onk)%10;
            onk=onk*10;
        }
    }


    int sayici=0;



    for(int i=0; i<500; i++)
    {
        toplam=0;
        sayi1=sayi[i][0]+sayi[i][1]*10+sayi[i][2]*100;
        sayi2=sayi[i][5]+sayi[i][4]*10+sayi[i][3]*100;
        sayi3=sayi[i][6]+sayi[i][7]*10+sayi[i][8]*100;



        toplam=sayi1+sayi2+sayi3;

        ind = toplam % 500;

        if (katlama_ayrik[ind]== NULL)
        {

            katlama_ayrik [ind]= new struct lineer;
            katlama_ayrik[ind]->adres = okunmus_dizii[i];
            katlama_ayrik[ind]->adi=ptr[i]->okunan_isim;
            katlama_ayrik[ind]->soyadi=dosya_okuyucu[i]->okunan_soyisim;
            katlama_ayrik[ind]->indeks=ind;


        }

        else
        {
            sayici=0;
            do
            {

                ind = ((ind)%500)+(sayici+500);
                sayici++;


            }
            while (katlama_ayrik[ind]!= NULL);
            katlama_ayrik[ind]= new struct lineer;
            katlama_ayrik[ind]->adres = okunmus_dizii[i];
            katlama_ayrik[ind]->indeks=ind;
            katlama_ayrik[ind]->adi=ptr[i]->okunan_isim;
            katlama_ayrik[ind]->soyadi=dosya_okuyucu[i]->okunan_soyisim;

        }





    }
    for(int i=0; i<1000; i++)
    {
        if(katlama_ayrik[i]==NULL)
        {
            fprintf(dosya4, "                     \n");
        }
        else
        {
            fprintf(dosya4,"%d %s %s\n",katlama_ayrik[i]->adres, katlama_ayrik[i]->adi, katlama_ayrik[i]->soyadi);
        }
    }

    fclose(dosya4);


}





void kare_ort_lineer(__int64 okunmus_dizi[500])
{

    dosya5=fopen("kare_lineer.txt", "w");
    __int64 karesi[500];

    int sayi1;
    int adr;
    __int64 sonuc=0;
    __int64 on_k=10;
    int basamak=1;
    for(int i=0; i<500; i++)
    {
        karesi[i]=okunmus_dizi[i]*okunmus_dizi[i];

    }


    //burda 7-10 arasýnda sayilari basamaklarýna ayýrma yöntemiyle alip sonuc adli deðiþkenimize atýyoruz basamaklarýna ayýrýken
    //yeni oluþacak olan sayinin basm. deðerleriyle carptik

    for(int i=0; i<500; i++)
    {
        sonuc=0;
        on_k=10000000;
        basamak=1;
        for(int j=0; j<4; j++)
        {
            sayi1=(karesi[i]/on_k)%10;
            sonuc=sonuc+(basamak*sayi1);
            on_k*=10;
            basamak*=10;

        }

        //cout<<"karesinin ortasi : "<<sonuc<<endl;




        adr = sonuc % 500;

        if (kare_lineer[adr]== NULL)
        {

            kare_lineer [adr]= new struct lineer;
            kare_lineer[adr]->adres = okunmus_dizi[i];
            kare_lineer[adr]->adi=ptr[i]->okunan_isim;
            kare_lineer[adr]->soyadi=dosya_okuyucu[i]->okunan_soyisim;
            kare_lineer[adr]->indeks=adr;

        }

        else
        {

            do
            {
                adr = (adr+ 1)%500;


            }
            while (kare_lineer[adr]!= NULL);
            kare_lineer[adr]= new struct lineer;
            kare_lineer[adr]->adres = okunmus_dizi[i];
            kare_lineer[adr]->indeks=adr;
            kare_lineer[adr]->adi=ptr[i]->okunan_isim;
            kare_lineer[adr]->soyadi=dosya_okuyucu[i]->okunan_soyisim;

        }


    }

    for(int i=0; i<500; i++)
    {
        fprintf(dosya5, "%d %s %s\n", kare_lineer[i]->adres, kare_lineer[i]->adi, kare_lineer[i]->soyadi);
    }
    fclose(dosya5);
}



void kare_ort_ayrik(__int64 okunmus_dizi[500])
{

    dosya6=fopen("kare_ort_ayrik.txt", "w");
    __int64 karesi[500];
    int sayici=0;
    int sayi1;
    int adr;
    __int64 sonuc=0;
    __int64 on_k=10;
    int basamak=1;
    for(int i=0; i<500; i++)
    {
        karesi[i]=okunmus_dizi[i]*okunmus_dizi[i];

    }




    for(int i=0; i<500; i++)
    {
        sonuc=0;
        on_k=10000000;
        basamak=1;
        for(int j=0; j<4; j++)
        {
            sayi1=(karesi[i]/on_k)%10;
            sonuc=sonuc+(basamak*sayi1);
            on_k*=10;
            basamak*=10;

        }

        adr = sonuc % 500;

        if (kare_ayrik[adr]== NULL)
        {

            kare_ayrik[adr]= new struct lineer;
            kare_ayrik[adr]->adres = okunmus_dizi[i];
            kare_ayrik[adr]->adi=ptr[i]->okunan_isim;
            kare_ayrik[adr]->soyadi=dosya_okuyucu[i]->okunan_soyisim;
            kare_ayrik[adr]->indeks=adr;


        }

        else
        {
            sayici=0;
            do
            {

                adr = ((adr)%500)+(sayici+500);
                sayici++;


            }
            while (kare_ayrik[adr]!= NULL);
            kare_ayrik[adr]= new struct lineer;
            kare_ayrik[adr]->adres = okunmus_dizi[i];
            kare_ayrik[adr]->indeks=adr;
            kare_ayrik[adr]->adi=ptr[i]->okunan_isim;
            kare_ayrik[adr]->soyadi=dosya_okuyucu[i]->okunan_soyisim;

        }

    }

    for(int i=0; i<2000; i++)
    {
        if(kare_ayrik[i]==NULL)
        {
            fprintf(dosya6, "                     \n");
        }
        else
        {
            fprintf(dosya6,"%d %s %s\n",kare_ayrik[i]->adres, kare_ayrik[i]->adi, kare_ayrik[i]->soyadi);

        }
    }

    fclose(dosya6);

}



void bolen_lineer_bul(int degisken)
{
    int sayac1=0;
    dosyaa=fopen("bolen_lineer.txt","r+");
    sayac1++;
    int adr1;
    //BURDA ADRESLERÝ BYTE SÝNÝN 2 FAZLASI
    int sayim;
    adr1=degisken%500;

    int ilk_adr;

    int y;
    int ilk_y;
    y=adr1*23;

    ilk_y=y;

    char ad1[5];
    char soyad1[5];

    fseek(dosyaa,y, SEEK_SET);
    fscanf(dosyaa, "%d %s %s", &sayim, ad1,soyad1);
    sayac1+=4;
    if(sayim==degisken)
    {

        cout<<"aranan sayi "<<adr1<<". adreste bulundu"<<endl;
        cout<<"OGRENCININ BILGILERI :"<<sayim<<" "<<ad1<<" "<<soyad1<<endl;
    }

    else
    {

        do
        {

            adr1=(adr1+1)%500;

            y=adr1*23;
            fseek(dosyaa,y,SEEK_SET);
            fscanf(dosyaa,"%d %s %s", &sayim, ad1,soyad1);
            sayac1+=3;


            //hash_okunan[i]=sayi;

            if(sayim==degisken)
            {
                cout<<"aranan sayi "<<adr1<<". de bulundu"<<endl;
                cout<<"OGRENCININ BILGILERI :"<<sayim<<" "<<ad1<<" "<<soyad1<<endl;

                break;
            }
            if(ilk_y==y)
            {
                cout<<"dosyanin sonu aranan deger bulunumadi : "<<endl;
                break;
            }

        }
        while(sayim!=degisken );


    }
    maliyet[1]=sayac1;
    cout<<"Arama "<<sayac1<<" adimda yapildi."<<endl;
    fclose(dosyaa);
}

void bolen_ayrik_bul(int aranan)
{
    int sayac2=0;
    dosya2=fopen("bolen_ayrik.txt","r+");
    sayac2++;
    int adr2;
    int sayi2;
    int z;
    int sayac;
    adr2=aranan%500;

    z=adr2*23;

    char ad2[5];
    char soyad2[5];
    fseek(dosya2, z,SEEK_SET);

    fscanf(dosya2, "%d %s %s", &sayi2, ad2,soyad2);
    sayac2+=3;
    if(sayi2==aranan)
    {
        cout<<"aranan sayi "<<adr2<<". adreste bulundu"<<endl;
        cout<<"OGRENCININ BILGILERI : "<<sayi2<<" "<<ad2<<" "<<soyad2<<endl;

    }

    else
    {
        //sayac belirtmemin nednei ayný kalaný çok kere vermesi
        sayac=0;
        sayac2++;
        do
        {


            adr2=((adr2)%500)+(sayac+500);
            z=adr2*23;
            sayac++;
            fseek(dosya2,z,SEEK_SET);
            fscanf(dosya2,"%d %s %s", &sayi2, ad2,soyad2);

            sayac2+=4;



            if(sayi2==aranan)
            {
                cout<<"aranan sayi "<<adr2<<". adreste bulundu"<<endl;
                cout<<"OGRENCININ BILGILERI : "<<sayi2<<" "<<ad2<<" "<<soyad2<<endl;
                break;
            }
            if(adr2>=1500)
            {
                cout<<"dosya sonu aranan deger bulunamadi."<<endl;
                break;
            }

        }
        while(sayi2!=aranan);

    }

    cout<<"Arama "<<sayac2<<" adimda yapildi."<<endl;
    maliyet[2]=sayac2;
    fclose(dosya2);


}

void katlama_lineer_bul(int aranan)
{
    int sayac3=0;
    dosya3=fopen("katlama_lineer.txt","r+");
    sayac3++;
    int katlama[10];
    int sayi3;
    int adr3;
    int onk=10;
    sayac3++;

    int z;
    int katli_toplam;
    int s1;
    int s2;
    int s3;
    int ilk_z;
    char ad3[5];
    char soyad3[5];

    katlama[0]=(aranan%10);
    sayac3++;
    for(int j=1; j<9; j++)
    {
        katlama[j]=(aranan/onk)%10;

        onk=onk*10;
        sayac3+=3; // J ÝÇÝNDE ATAMA YAPAR O YÜZDEN +3
    }


    s1=katlama[0]+katlama[1]*10+katlama[2]*100;
    s2=katlama[5]+katlama[4]*10+katlama[3]*100;
    s3=katlama[6]+katlama[7]*10+katlama[8]*100;

    katli_toplam=s1+s2+s3;
    sayac3++;

    adr3=katli_toplam%500;
    sayac3+=5;

    z=adr3*23;
    sayac3++;

    ilk_z=z;
    sayac3++;

    fseek(dosya3,z,SEEK_SET);
    fscanf(dosya3,"%d %s %s", &sayi3,ad3,soyad3);
    sayac3++;
    if(sayi3==aranan)
    {
        cout<<"Aranan sayi "<<adr3<<". adreste bulundu"<<endl;
        cout<<"OGRENCININ BILGILERI : "<<sayi3<<" "<<ad3<<" "<<soyad3<<endl;
    }
    else
    {
        do
        {
            adr3=(adr3+1)%500;


            z=adr3*23;


            fseek(dosya3,z,SEEK_SET);
            fscanf(dosya3,"%d %s %s", &sayi3,ad3,soyad3);

            sayac3+=3;
            if(sayi3==aranan)
            {
                cout<<"aranan sayi "<<adr3<<". adreste bulundu : "<<endl;
                cout<<"OGRENCININ BILGILERI : "<<sayi3<<" "<<ad3<<" "<<soyad3<<endl;
                break;
            }

            if(z==ilk_z)
            {
                cout<<"dosya sonu aranan deger bulunamadi. "<<endl;
                break;
            }
        }
        while(sayi3!=aranan);

    }


    cout<<"Arama "<<sayac3<<" adimda yapildi."<<endl;
    maliyet[3]=sayac3;

    fclose(dosya3);



}

void katlama_ayrik_bul(int aranan)
{

    int sayac4=0;
    dosya4=fopen("katlama_ayrik_tasma.txt","r+");
    sayac4++;
    int sayac=0;
    sayac4++;
    int katlama_ayr[10];
    int katli_toplam_ayr=0;
    sayac4++;
    int onkk=10;
    int m=0;
    sayac4+2;
    int s1;
    int s2;
    int s3;
    int ilk_adr4;
    int adr4;
    int sayi4;
    char ad4[5];
    char soyad4[5];
    katlama_ayr[0]=(aranan%10);
    sayac4++;
    for(int j=1; j<9; j++)
    {
        katlama_ayr[j]=(aranan/onkk)%10;
        onkk=onkk*10;

        sayac4=sayac4+3; // J için yaptýðý atamayýda aldýk
    }


    s1=katlama_ayr[0]+katlama_ayr[1]*10+katlama_ayr[2]*100;
    s2=katlama_ayr[5]+katlama_ayr[4]*10+katlama_ayr[3]*100;
    s3=katlama_ayr[6]+katlama_ayr[7]*10+katlama_ayr[8]*100;

    katli_toplam_ayr=s1+s2+s3;

    adr4=katli_toplam_ayr%500;
    m=adr4*23;
    ilk_adr4=adr4;
    sayac4+=7;
    fseek(dosya4,m,SEEK_SET);
    fscanf(dosya4,"%d %s %s", &sayi4,ad4,soyad4);
    sayac4++;
    if(sayi4==aranan)
    {
        cout<<"aranan sayi "<<adr4<<". adreste bulundu"<<endl;

        cout<<"OGRENCININ BILGILERI : "<<sayi4<<" "<<ad4<<" "<<soyad4<<endl;
    }

    else
    {
        sayac=0;
        sayac4++;
        do
        {
            adr4=((adr4)%500)+(sayac+500);
            m=adr4*23;
            sayac++;
            fseek(dosya4,m,SEEK_SET);
            fscanf(dosya4,"%d %s %s", &sayi4, ad4,soyad4);
            sayac4+=4;
            if(sayi4==aranan)
            {
                cout<<"aranan sayi "<<adr4<<". adreste bulundu"<<endl;
                cout<<"OGRENCININ BILGILERI : "<<sayi4<<" "<<ad4<<" "<<soyad4<<endl;
                break;
            }
            if(adr4>=1500)
            {

                cout<<"dosya sonu aranan deger bulunamadi "<<endl;
                break;
            }

        }
        while(sayi4!=aranan);

    }

    cout<<"Arama "<<sayac4<<" adimda yapildi."<<endl;
    maliyet[4]=sayac4;
    fclose(dosya4);
}




void kare_ort_lineer_bul(__int64 aranan)
{
    int sayac5=0;
    dosya5=fopen("kare_lineer.txt","r+");
    sayac5++;
    __int64 arananin_karesi;
    int adr5;
    int ilk_adr5;
    int sayi5;
    __int64 sonuc=0;
    __int64 on_k=10000000;
    int basm_degeri=1;
    int sayi_degerleri;
    int n;
    char ad5[5];
    char soyad5[5];

    arananin_karesi=aranan*aranan;
    sayac5+=4;
    for(int i=0; i<4; i++)
    {
        sayi_degerleri=(arananin_karesi/on_k)%10;//sirasiyla 7-8-9-10. basamaklardaki sayilari tutar.
        sonuc=sonuc+(basm_degeri*sayi_degerleri);//burdada 4 haneli(1000'leer) sayi olusturur
        on_k=on_k*10;
        basm_degeri=basm_degeri*10;
        sayac5+=5;
    }


    adr5=sonuc%500;
    ilk_adr5=adr5;

    n=adr5*23;
    int 	ilk_n=n;
    fseek(dosya5,n,SEEK_SET);
    fscanf(dosya5, "%d %s %s ", &sayi5, ad5,soyad5);
    sayac5+5;
    if(sayi5==aranan)
    {
        cout<<"aranan sayi "<<adr5<<". adreste bulundu"<<endl;
        cout<<"OGRENCININ BILGILERI : "<<sayi5<<" "<<ad5<<" "<<soyad5<<endl;

    }
    else
    {

        do
        {

            adr5=(adr5+1)%500;
            n=adr5*23;

            fseek(dosya5,n, SEEK_SET);
            fscanf(dosya5,"%d %s %s", &sayi5,ad5,soyad5);
            sayac5+=3;
            if(sayi5==aranan)
            {
                cout<<"aranan sayi "<<adr5<<". adreste bulundu"<<endl;
                cout<<"OGRENCININ BILGILERI : "<<sayi5<<" "<<ad5<<" "<<soyad5<<endl;
            }

            if(n==ilk_n)
            {
                cout<<"dosya sonu aranan deger bulunamadi."<<endl;
                break;
            }

        }
        while(sayi5!=aranan);
    }

    cout<<"Arama "<<sayac5<<" adimda yapildi."<<endl;
    maliyet[5]=sayac5;
    fclose(dosya5);
}


void kare_ort_ayrik_bul(__int64 aranan)
{
    int sayac6=0;
    dosya6=fopen("kare_ort_ayrik.txt","r+");
    sayac6++;
    __int64 arananin_karesi2;
    int sayi6;
    int k;
    int ilk_k;
    int adr6;
    __int64 onk_6=10000000;
    arananin_karesi2=aranan*aranan;
    int rakam;
    int basm_deg=1;
    __int64 sonuc2=0;
    int sayac=0;
    char ad6[5];
    char soyad6[5];

    sayac6+=5;

    for(int i=0; i<4; i++)
    {
        rakam=(arananin_karesi2/onk_6)%10;//sirasiyla 7-8-9-10. basamaklardaki sayilari tutar.
        sonuc2=sonuc2+(basm_deg*rakam);//burdada 4 haneli(1000'leer) sayi olusturur
        onk_6*=10;
        basm_deg*=10;

        sayac6+=5;
    }

    adr6=(int)sonuc2%500;//(int) yapmasakta olur

    k=adr6*23;
    ilk_k=k;

    fseek(dosya6, k, SEEK_SET);
    fscanf(dosya6,"%d %s %s",&sayi6, ad6,soyad6);

    sayac6+=4;

    if(sayi6==aranan)
    {
        cout<<"aranan sayi "<<adr6<<". adreste bulundu"<<endl;
        cout<<"OGRENCININ BILGILERI : "<<sayi6<<" "<<ad6<<" "<<soyad6<<endl;
    }
    else
    {
        sayac=0;
        do
        {

            adr6=(adr6%500)+(sayac+500);

            k=adr6*23;
            sayac++;
            fseek(dosya6, k, SEEK_SET);
            fscanf(dosya6, "%d %s %s", &sayi6,ad6,soyad6);
            sayac6+=4;
            if(sayi6==aranan)
            {
                cout<<"aranan sayi "<<adr6<<". adreste bulundu"<<endl;
                cout<<"OGRENCININ BILGILERI : "<<sayi6<<" "<<ad6<<" "<<soyad6<<endl;
                break;
            }

            if(adr6>=15000)
            {
                cout<<"dosya sonu aranan deger bulunamadi."<<endl;
                break;
            }


        }
        while(sayi6!=aranan);

    }
    cout<<"Arama "<<sayac6<<" adimda yapildi."<<endl;
    maliyet[6]=sayac6;
    fclose(dosya6);
}


void random_dosya_ara(int aranan)
{
    int sayac0=0;
    dosya=fopen("random.txt","r+");
    sayac0++;
    int ogr_no;
    int ogr_dizi[500];
    int i=0;
    sayac0++;
    char ismi[5];
    char isim_kopya[500];
    char soyadi[5];
    char soyadi_kopya[500];

    while(!feof(dosya))
    {
        dosya_okuyucu[i]=new struct lineer;

        fscanf(dosya,"%d %s %s", &ogr_no,ismi,soyadi);
        ogr_dizi[i]=ogr_no;
        strcpy(dosya_okuyucu[i]->okunan_isim,ismi);
        sayac0+=4;



        if(aranan==ogr_dizi[i])
        {
            cout<<"aranan ogrenci kayitli "<<endl;

            cout<<"OGRENCININ BILGILERI : "<<ogr_dizi[i]<<" "<<dosya_okuyucu[i]->okunan_isim<<" "<<soyadi<<endl;
            break;
        }
        i++;
        sayac0++;
        if(i==500)
        {
            cout<<"dosya sonu aranan kayit bulunamadi "<<endl;
        }
    }

    cout<<"Arama "<<sayac0<<" adimda yapildi"<<endl;
    maliyet[0]=sayac0;
    fclose(dosya);

}




void maliyet_hesapla()
{
    int yedek_maliyet[7];
    for(int i=0; i<7; i++)
    {
        yedek_maliyet[i]=maliyet[i];
    }
    int gecici;

    for(int i=0; i<6; i++)
    {

        for(int k=0; k<6-i; k++)
        {
            if(maliyet[k]>maliyet[k+1])
            {
                gecici=maliyet[k];
                maliyet[k]=maliyet[k+1];
                maliyet[k+1]=gecici;
            }
        }
    }
    cout<<endl;
    cout<<"EN AZ MALIYETLI DOSYA :"<<endl;
    if(maliyet[0]==yedek_maliyet[0])
    {
        cout<<"RANDOM DOSYA.txt";
    }
    else if(maliyet[0]==yedek_maliyet[1])
    {
        cout<<"BOLEN_LINEER.txt "<<endl;
    }
    else if(maliyet[0]==yedek_maliyet[2])
    {
        cout<<"BOLEN_AYRIK.txt  "<<endl;
    }
    else if(maliyet[0]==yedek_maliyet[3])
    {
        cout<<"KATLAMA_LINEER.txt"<<endl;
    }
    else if(maliyet[0]==yedek_maliyet[4])
    {
        cout<<"KATLAMA_AYRIK_TASMA.txt"<<endl;
    }
    else if(maliyet[0]==yedek_maliyet[5])
    {
        cout<<"KARE_LINEER.txt "<<endl;
    }

    else if(maliyet[0]==yedek_maliyet[6])
    {
        cout<<"KARE_ORT_AYRIK.txt "<<endl;
    }


}
