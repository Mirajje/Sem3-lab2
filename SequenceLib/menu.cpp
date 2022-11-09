#ifndef CPP_MENU
#define CPP_MENU

template<class T>
void input(T* a)
{
    while (true)
    {
        std::cout << "Enter a value:";
        std::cin >> *a;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            continue;
        }
        break;
    }
}

void menu()
{
    printf("Enter 1 for ListSequence, 2 for ArraySequence\n");
    int t = -1;
    while (t != 1 && t != 2)
        input(&t);

    Sequence<int>* seq;

    if (t == 1)
        seq = new ListSequence<int>;
    else
        seq = new ArraySequence<int>;

    printf("Enter 1 for append, 2 for prepend, 3 for insertAt, 4 for find, 5 for getLength, 6 for set, 7 for pop, 8 for print, 9 for exit program\n");
    while (true)
    {
        t = -1;
        int index;
        while (t < 1 || t > 9)
        {
            printf("Enter a command: \n");
            input(&t);
        }


        switch (t)
        {
            case 9:
                exit(0);
                break;

            case 1:
                seq->append(0);
                printf("Enter append item\n");
                input(&(*seq)[seq->getLength()-1]);
                break;

            case 2:
                seq->prepend(0);
                printf("Enter prepend item\n");
                input(&(*seq)[0]);
                break;

            case 3:
                printf("Enter insert index\n");
                input(&index);
                try
                {
                    seq->insertAt(0, index);
                    printf("Enter insert item\n");
                    input(&(*seq)[index]);
                }
                catch (const Errors& error)
                {
                    std::cout << "Process finished with error code = " << error << std::endl;
                    exit(0);
                }
                break;

            case 8:
                seq->print();
                break;

            case 4:
                printf("Enter item to find\n");
                int item;
                input(&item);
                std::cout << "The first occurrence position is: " << seq->find(item) << std::endl;
                break;

            case 5:
                std::cout << "The length is: " << seq->getLength() << std::endl;
                break;

            case 6:
                printf("Enter set item\n");
                input(&item);
                printf("Enter set index\n");
                input(&index);
                try
                {
                    seq->set(item, index);
                }
                catch (const Errors& error)
                {
                    std::cout << "Process finished with error code = " << error << std::endl;
                    exit(0);
                }
                break;

            case 7:
                printf("Enter pop index\n");
                input(&index);

                try
                {
                    item = seq->pop(index);
                }
                catch (const Errors& error)
                {
                    std::cout << "Process finished with error code = " << error << std::endl;
                    exit(0);
                }

                std::cout << "Popped item is: " << item << std::endl;
                break;
        }
    }

}

#endif