#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct contact {
    long ph;
    char name[20], add[20], email[30];
} list;

char query[20], name[20];

fstream fp, ft;

int i, n, ch, l, found;

void addContact() {
    fp.open("contact.dll", ios::out | ios::app);

    for (;;) {
        cin.ignore();
        cout << "To exit, enter a blank space in the name input\nName (Use identical): ";
        cin.getline(list.name, 20);

        if (strcmp(list.name, "") == 0 || strcmp(list.name, " ") == 0)
            break;

        cout << "Phone: ";
        cin >> list.ph;
        cin.ignore();

        cout << "Address: ";
        cin.getline(list.add, 20);

        cout << "Email address: ";
        cin.getline(list.email, 30);

        cout << endl;

        fp.write(reinterpret_cast<char *>(&list), sizeof(list));
    }

    fp.close();
}

void listContacts() {
    cout << "\n\t\t================================\n\t\t\tLIST OF CONTACTS\n\t\t================================\n";
    cout << "Name\t\tPhone No\t    Address\t\tE-mail ad.\n";
    cout << "=================================================================\n\n";

    for (i = 97; i <= 122; i = i + 1) {
        fp.open("contact.dll", ios::in);
        cin.ignore();

        found = 0;

        while (fp.read(reinterpret_cast<char *>(&list), sizeof(list))) {
            if (list.name[0] == i || list.name[0] == i - 32) {
                cout << "Name\t: " << list.name << endl;
                cout << "Phone\t: " << list.ph << endl;
                cout << "Address\t: " << list.add << endl;
                cout << "Email\t: " << list.email << endl;
                cout << endl;

                found++;
            }
        }

        if (found != 0) {
            cout << "=========================================================== [" << static_cast<char>(i - 32) << "]-(" << found << ")\n\n";
            cin.get();
        }

        fp.close();
    }
}

void searchContact() {
    do {
        found = 0;

        cout << "\n\n\t..::CONTACT SEARCH\n\t===========================\n";
        cout << "\t..::Name of contact to search: ";
        cin.ignore();
        cin.getline(query, 20);

        l = strlen(query);

        fp.open("contact.dll", ios::in);
        system("cls");

        cout << "\n\n..::Search result for '" << query << "'\n===================================================\n";

        while (fp.read(reinterpret_cast<char *>(&list), sizeof(list))) {
            for (i = 0; i <= l; i++)
                name[i] = list.name[i];

            name[l] = '\0';

            if (strcmp(name, query) == 0) {
                cout << "..::Name\t: " << list.name << endl;
                cout << "..::Phone\t: " << list.ph << endl;
                cout << "..::Address\t: " << list.add << endl;
                cout << "..::Email\t: " << list.email << endl;

                found++;

                if (found % 4 == 0) {
                    cout << "..::Press any key to continue...";
                    cin.get();
                }
            }
        }

        if (found == 0){
            cout << "\n..::No match found!";
        }
        else
        {
            cout << "\n..::" << found << " match(es) found!";
        }

        fp.close();

        cout << "\n ..::Try again?\n\n\t[1] Yes\t\t[0] No\n\t";
        cin >> ch;
    } while (ch == 1);
}

void editContact()
{
    fp.open("contact.dll", ios::in);
    ft.open("temp.dat", ios::out);

    cin.ignore();
    cout << "..::Edit contact\n===============================\n\n\t..::Enter the name of contact to edit: ";
    cin.getline(name, 20);

    while (fp.read(reinterpret_cast<char *>(&list), sizeof(list)))
    {
        if (strcmp(name, list.name) != 0)
            ft.write(reinterpret_cast<char *>(&list), sizeof(list));
    }

    cin.ignore();
    cout << "\n\n..::Editing '" << name << "'\n\n";
    cout << "..::Name (Use identical): ";
    cin.getline(list.name, 20);

    cout << "..::Phone: ";
    cin >> list.ph;
    cin.ignore();

    cout << "..::Address: ";
    cin.getline(list.add, 20);

    cout << "..::Email address: ";
    cin.getline(list.email, 30);

    cout << endl;

    ft.write(reinterpret_cast<char *>(&list), sizeof(list));

    fp.close();
    ft.close();

    remove("contact.dll");
    rename("temp.dat", "contact.dll");
}

void deleteContact()
{
    cin.ignore();
    cout << "\n\n\t..::DELETE A CONTACT\n\t==========================\n\t..::Enter the name of contact to delete: ";
    cin.getline(name, 20);

    fp.open("contact.dll", ios::in);
    ft.open("temp.dat", ios::out);

    while (fp.read(reinterpret_cast<char *>(&list), sizeof(list)))
    {
        if (strcmp(name, list.name) != 0)
            ft.write(reinterpret_cast<char *>(&list), sizeof(list));
    }

    fp.close();
    ft.close();

    remove("contact.dll");
    rename("temp.dat", "contact.dll");
}

int main()
{
    int ch;
    do
    {
        system("cls");
        cout << "\n\t **** Welcome to Contact Management System ****";
        cout << "\n\n\n\t\t\tMAIN MENU\n\t\t=====================\n\t\t[1] Add a new Contact\n\t\t[2] List all Contacts\n\t\t[3] Search for contact\n\t\t[4] Edit a Contact\n\t\t[5] Delete a Contact\n\t\t[0] Exit\n\t\t=================\n\t\t";
        cout << "Enter the choice: ";
        cin >> ch;

        switch (ch)
        {
        case 0:
            cout << "\n\n\t\tAre you sure you want to exit?";
            break;
        case 1:
            system("cls");
            addContact();
            break;
        case 2:
            system("cls");
            listContacts();
            cin.get();
            break;
        case 3:
            system("cls");
            searchContact();
            cin.get();
            break;
        case 4:
            system("cls");
            editContact();
            break;
        case 5:
            system("cls");
            deleteContact();
            break;
        default:
            cout << "Invalid choice";
            break;
        }

        cout << "\n\n\n..::Enter the Choice:\n\n\t[1] Main Menu\t\t[0] Exit\n";
        cin >> ch;

        switch (ch)
        {
        case 1:
            break;
        case 0:
            break;
        default:
            cout << "Invalid choice";
            break;
        }

    } while (ch != 0);

    return 0;
}


