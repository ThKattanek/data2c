// Code by Thorsten Kattanek //
// Datei wird in TextDatei gewandelt //

//#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

FILE *s_file = NULL;
fstream d_file;
string puffer_name;
unsigned char read_puffer;

void help_out(void)
{
    cout << "Aufruf: data2c QUELLDATEI... [ZIELDATEI]... [PUFFERNAME]... [OPTION]..." << endl;
    cout << "Wandelt die Quelldatei in eine C Headerdatei um." << endl << endl;
    cout << "--help\t\tdiese Hilfe anzeigen und beenden" << endl;
    cout << "--version\tVersionsinformation anzeigen und beenden" << endl;
}

int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        if(strcmp(argv[1],"--help") == 0)
        {
            help_out();
            return (0);
        }

        if(strcmp(argv[1],"--version") == 0)
        {
            cout << "Version 0.10 [Code by Thorsten Kattanek (C)2012]" << endl;
            return (0);
        }
    }

    if(argc < 2)
    {
        cout << "data2c: Fehlender Operand." << endl;
        cout << "'data2c --help' gibt weitere Informationen." << endl;
        return(0);
    }

    switch(argc)
    {
    case 0: case 1:
        // Kann nicht vorkommen da oben schon beendet wurde (argc < 2) return !!
        break;
    case 2:     // Nur eine Quelldatei wurde angegeben
        s_file = fopen(argv[1],"r+b");
        if(s_file == NULL)
        {
            cerr << "Quelldatei konnte nicht geoeffnet werden, oder existiert nicht." << endl;
            return (0);
        }

        char fname[512];
        sprintf(fname,"%s.h",argv[1]);

        d_file.open(fname,ios::out);
        if(!d_file.is_open())
        {
            cerr << "Zieldatei konnte nicht erstellet werden" << endl;
            fclose(s_file);
            return (0);
        }

        puffer_name = "raw_data";

        break;
    case 3:     // Quell- und Zieldatei wurde angegeben
        s_file = fopen(argv[1],"r+b");
        if(s_file == NULL)
        {
            cerr << "Quelldatei konnte nicht geoeffnet werden, oder existiert nicht." << endl;
            return (0);
        }

        d_file.open(argv[2],ios::out);
        if(!d_file.is_open())
        {
            cerr << "Zieldatei konnte nicht erstellet werden" << endl;
            fclose(s_file);
            return (0);
        }

        puffer_name = "raw_data";

        break;

    case 4:     // Quell- und Zieldatei wurde angegeben sowie ein PufferName
        s_file = fopen(argv[1],"r+b");
        if(s_file == NULL)
        {
            cerr << "Quelldatei konnte nicht geoeffnet werden, oder existiert nicht." << endl;
            return (0);
        }

        d_file.open(argv[2],ios::out);
        if(!d_file.is_open())
        {
            cerr << "Zieldatei konnte nicht erstellet werden" << endl;
            fclose(s_file);
            return (0);
        }

        puffer_name = argv[3];

        break;

    default:
        s_file = fopen(argv[1],"r+b");
        if(s_file == NULL)
        {
            cerr << "Quelldatei konnte nicht geoeffnet werden, oder existiert nicht." << endl;
            return (0);
        }

        d_file.open(argv[2],ios::out);
        if(!d_file.is_open())
        {
            cerr << "Zieldatei konnte nicht erstellet werden" << endl;
            fclose(s_file);
            return (0);
        }

        puffer_name = argv[3];

        //// Optionen auslesen ////
        for(int i=4;i<argc;i++)
        {

        }

        break;
    }

    long length = 0;
    char str_out[256];

    d_file << "// " << puffer_name << " erstellt mit data2c von Thorsten Kattanek" << endl;
    d_file << "const unsigned char " << puffer_name << "[] ={" << endl;

    int counter = 0;

    while(fread(&read_puffer,1,1,s_file) == 1)
    {
        length++;
        sprintf(str_out,"0x%2.2X",read_puffer);
        d_file << str_out << ",";
        if(counter == 19)
        {
            counter = 0;
            d_file << endl;
        }
        else counter++;
    }

    d_file << "};" << endl;
    sprintf(str_out,"%d",(int)length);
    d_file << "const int " << puffer_name << "_length = " << str_out << ";";

    fclose(s_file);
    d_file.close();

    return (0);
}
