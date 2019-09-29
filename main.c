#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    char *dig;	// массив для хранения числа:
// a[0] * 100^0 + a[1] * 100^1 + .. + a[n - 1] * 100^(n-1)
    int n; 			// размер числа в разрядах
    char sign;	// знак числа
}LongN;

LongN getLongN (char * s);

void show(LongN a);

void showDeb(LongN a);

LongN * maxLN(LongN * a, LongN * b);

LongN * minLN(LongN * a, LongN * b);

void invertLN(LongN *numb);

LongN sumLN(LongN a, LongN b);

LongN copyLN(LongN * a);

LongN mult2(LongN * a);

LongN div2(LongN * a);

LongN multLN(LongN a, LongN b);

LongN divLN(LongN a, LongN b);

LongN powLN (LongN * a, int power);

int main () {
    int i = 0;
    int power;
    int len1 = 0, len2 = 0;
    printf("-------------------------------------------------------------------------\n");
    printf("|                           Enter two numbers                           |\n");
    printf("-------------------------------------------------------------------------\n");
    char *s1 = malloc(200* sizeof(char));
    char *s2 = malloc(200* sizeof(char));
    AGAIN:
    scanf("%s", s1);
    if (s1[0] == 'e' || s1[0] == '\n')
        goto END;
    scanf("%s", s2);
    len1 = strlen(s1);
    len2 = strlen(s2);
    for (i = 0; i < len1; i++)
        if (isdigit(s1[i]) == 0) {
            if ((s1[i] != '+') && (s1[i] != '-')) {
                printf("-------------------------------------------------------------------------\n");
                printf("|                        Error, it is not numbers                       |\n");
                printf("-------------------------------------------------------------------------\n");
                goto NEW;
            }
        }
    for (i = 0; i < len2; i++)
        if (isdigit(s2[i]) == 0) {
            if ((s2[i] != '+') && (s2[i] != '-')) {
                printf("-------------------------------------------------------------------------\n");
                printf("|                        Error, it is not numbers                       |\n");
                printf("-------------------------------------------------------------------------\n");
                goto NEW;
            }
        }

    LongN numb1 = getLongN(s1);
    LongN numb2 = getLongN(s2);

    printf("-------------------------------------------------------------------------\n");
    printf("|                          Enter positive power                         |\n");
    printf("-------------------------------------------------------------------------\n");

    scanf ("%d", &power);

    // первое число
    printf("Number 1 : ");
    show (numb1);
    printf ("Number in memory 1 : ");
    showDeb (numb1);
    LongN mult1 = mult2(&numb1);
    printf ("Number 1 multiplied by 2 : ");
    show(mult1);
    LongN pow1 = powLN(&numb1, power);
    printf ("Number 1 power by %d : ", power);
    show(pow1);

    printf("\n");

    // Второе число
    printf ("Number 2 : ");
    show (numb2);
    printf ("Number in memory 2 : ");
    showDeb(numb2);
    LongN div1 = div2(&numb2);
    printf ("Number 2 divided by 2 : ");
    show(div1);
    LongN pow2 = powLN(&numb2, power);
    printf ("Number 2 power by %d : ", power);
    show(pow2);

    printf("\n");

    // Сумма
    LongN sum = sumLN(numb1, numb2);
    printf ("Number sum : ");
    show (sum);
    printf ("Number in memory sum : ");
    showDeb(sum);

    printf("\n");

    // Умножение
    LongN mult = multLN(numb1, numb2);
    printf ("Number multiplied : ");
    show (mult);
    printf ("Number in memory multiplied : ");
    showDeb(mult);

    printf("\n");

    // Деление
    LongN div = divLN(numb1, numb2);
    printf ("Number division : ");
    show (div);
    printf ("Number in memory division : ");
    showDeb(div);

    printf("\n");

    // Отчистка памяти
    free(numb1.dig);
    free(numb2.dig);
    free(sum.dig);
    free(mult1.dig);
    free(div1.dig);
    free(mult.dig);
    free(div.dig);
    free(pow1.dig);
    free(pow2.dig);

    NEW:
    printf("-------------------------------------------------------------------------\n");
    printf("|          Enter < e > to end or enter two numbers to continue          |\n");
    printf("-------------------------------------------------------------------------\n");
    goto AGAIN;
    END:
    free(s1);
    free(s2);
    return 0;
}

LongN getLongN(char * s) {
    LongN numb;
    char* str = malloc(200* sizeof(char));
    strcpy(str, s);
    int len = strlen(str);
    int i, j;
    if (str[0] >= 48 && str[0]<=58) {
        for (i = 0; i < len; i++)
            str[i] -= '0';
        if (len % 2 == 0)
            numb.n = len / 2;
        else
            numb.n = len / 2 + 1;
        numb.dig = malloc(numb.n * sizeof(char));
        numb.sign = 0;
        for (i = 0, j = (len - 1); i < numb.n; i++) {
            if (j - 1 >= 0) {
                numb.dig[i] = (char)(str[j] + 10 * str[j - 1]);
            } else {
                numb.dig[i] = str[j];
            }
            j -= 2;
        }
        if (numb.n != 1) {
            for (i = numb.n; numb.dig[i - 1] == 0; i--);
            numb.dig = realloc(numb.dig, i * sizeof(char));
            numb.n = i;
        }
        free(str);
        return numb;
    } else if (str[0] == '+') {
        numb.sign = 0;
        for (i = 0; i < len - 1; i++)
            str[i] = str[i + 1];
        for (i = 0; i < len; i++)
            str[i] -= '0';
        len--;
        if (len % 2 == 0)
            numb.n = len / 2;
        else
            numb.n = len / 2 + 1;
        numb.dig = malloc(numb.n * sizeof(char));
        numb.sign = 0;
        for (i = 0, j = (len - 1); i < numb.n; i++) {
            if (j - 1 >= 0) {
                numb.dig[i] = (char)(str[j] + 10 * str[j - 1]);
            } else {
                numb.dig[i] = str[j];
            }
            j -= 2;
        }
        if (numb.n != 1) {
            for (i = numb.n; numb.dig[i - 1] == 0; i--);
            numb.dig = realloc(numb.dig, i * sizeof(char));
            numb.n = i;
        }
        free(str);
        return numb;
    } else if (str[0] == '-') {
        numb.sign = 1;
        for (i = 0; i < len - 1; i++)
            str[i] = str[i + 1];
        for (i = 0; i < len - 1; i++)
            str[i] -= '0';
        len--;
        if (len % 2 == 0)
            numb.n = len / 2;
        else
            numb.n = len / 2 + 1;
        numb.dig = malloc(numb.n * sizeof(char));
        for (i = 0, j = (len - 1); i < numb.n; i++, j -= 2) {
            if (j - 1 >= 0) {
                numb.dig[i] = (char)(str[j] + 10 * str[j - 1]);
            } else {
                numb.dig[i] = str[j];
            }
        }
        free(str);
        if (numb.n != 1) {
            for (i = numb.n; numb.dig[i - 1] == 0; i--);
            numb.dig = realloc(numb.dig, i * sizeof(char));
            numb.n = i;
        }
        return numb;
    } else {
        numb.dig = NULL;
        numb.sign = 2;
        numb.n = 0;
        free(str);
        return numb;
    }
}

void show (LongN a) {
    if (a.sign == 2) {
        printf ("ERROR : cannot divide by zero\n");
    } else {
        int i;
        if (a.sign == 1)
            printf("- ");
        else
            printf("+ ");
        for (i = a.n - 1; i >= 0; i--) {
            if (a.dig[i] / 10 == 0 && i != a.n - 1)
                printf("0%d ", a.dig[i]);
            else
                printf("%d ", a.dig[i]);
        }
        printf("\n");
    }
}

void showDeb(LongN a) {
    if (a.sign == 2) {
        printf("ERROR : cannot divide by zero\n");
    } else {
        int i;
        printf("%d   ", a.sign);
        for (i = 0; i < a.n; i++) {
            printf("%d ", a.dig[i]);
        }
        printf("\n");
    }
}

LongN * maxLN(LongN * a, LongN * b) {
    if (a->n > b->n) {
        return a;
    }
    if (a->n < b->n) {
        return b;
    }
    int i = 0;
    for (i = a->n-1; i >= 0; i--) {
        if (a->dig[i] > b->dig[i])
            return a;
        if (a->dig[i] < b->dig[i])
            return b;
    }
    if (a->sign < b->sign)
        return a;
    if (a->sign > b->sign)
        return b;
    return a;
}

LongN * minLN(LongN * a, LongN * b) {
    if (a->n < b->n) {
        return a;
    }
    if (a->n > b->n) {
        return b;
    }
    int i = 0;
    for (i = a->n-1; i >= 0; i--) {
        if (a->dig[i] < b->dig[i])
            return a;
        if (a->dig[i] > b->dig[i])
            return b;
    }
    if (a->sign > b->sign)
        return a;
    if (a->sign < b->sign)
        return b;
    return b;
}

void invertLN(LongN *numb) {
    LongN obr;
    obr.sign = numb->sign;
    int i = 0;
    obr.n = numb->n;
    obr.dig = malloc(obr.n * sizeof(char));
    obr.dig[0] = (char)(100 - numb->dig[0]);
    for (i = 1; i < obr.n; i++) {
        obr.dig[i] = (char)(99 - numb->dig[i]);
    }
    for (i = 0; i < obr.n - 1; i++) {
        if (obr.dig[i] >= 100) {
            obr.dig[i] -= 100;
            obr.dig[i + 1] += 1;
        }
    }
    free(numb->dig);
    *numb = obr;
}

LongN sumLN (LongN a, LongN b) {
    LongN sum;
    LongN * max = maxLN(&a, &b);
    LongN * min = minLN(&a, &b);
    int i = 0;
    char over = 0;
    unsigned char pre = 0;

    //Одинаковые знаки у чисел

    if (max->sign == min->sign) {
        sum.dig = malloc((max->n + 1) * sizeof(char));
        sum.sign = max->sign;
        for (i = 0; i < min->n; i++) {
            pre = (unsigned char)(max->dig[i] + min->dig[i] + over);
            if (pre >=100) {
                over = 1;
                sum.dig[i] = (char)(pre - 100);
            } else {
                sum.dig[i] = pre;
                over = 0;
            }
        }

        for (i = min->n; i < max->n; i++) {
            pre = (unsigned char)(max->dig[i] + over);
            if (pre >=100) {
                over = 1;
                sum.dig[i] = (char)(pre - 100);
            } else {
                sum.dig[i] = pre;
                over = 0;
            }
        }
        sum.n = max->n;
        if (over == 1) {
            sum.dig[max->n] = over;
            sum.n++;
        }
    }

    //разные знаки у чисел

    if (max->sign != min->sign) {
        sum.dig = malloc(max->n * sizeof(char));
        LongN numbHelp1;
        int k = 0;
        sum.n = max->n;
        sum.sign = max->sign;
        numbHelp1.n = max->n;
        numbHelp1.dig = malloc(max->n * sizeof(char));
        LongN numbHelp2 = copyLN(max);

        if (max->sign == 1) {
            invertLN (&numbHelp2);
            numbHelp1.sign = 0;

            for (i = 0, k = 0; k < max->n; i++, k++) {
                if (i < min->n)
                    numbHelp1.dig[k] = min->dig[i];
                else
                    numbHelp1.dig[k] = 0;
            }
        }
        else {
            numbHelp1.sign = 1;

            for (i = 0, k = 0; k < max->n; i++, k++) {
                if (i < min->n)
                    numbHelp1.dig[k] = min->dig[i];
                else
                    numbHelp1.dig[k] = 0;
            }
            invertLN(&numbHelp1);
        }
        for (i = 0; i < max->n; i++) {
            pre = (unsigned char)(numbHelp2.dig[i] + numbHelp1.dig[i] + over);
            if (pre >= 100) {
                over = 1;
                sum.dig[i] = (char)(pre - 100);
            } else {
                over = 0;
                sum.dig[i] = pre;
            }
        }
        if (over != 1)
            invertLN(&sum);

        free(numbHelp1.dig);
        free(numbHelp2.dig);
    }
    if (sum.n != 1) {
        for (i = sum.n; sum.dig[i - 1] == 0; i--);
        sum.dig = realloc(sum.dig, i * sizeof(char));
        sum.n = i;
    }
    else
        sum.n = 1;
    return sum;
}

LongN copyLN(LongN * a) {
    LongN copy;
    int i = 0;
    copy.n = a->n;
    copy.sign = a->sign;
    copy.dig = malloc(copy.n * sizeof(char));
    for (i = 0; i < copy.n; i++) {
        copy.dig[i] = a->dig[i];
    }
    return copy;
}

LongN mult2(LongN * a) {
    LongN mult;
    int i = 0;
    char over = 0;
    unsigned char pre = 0;

    mult.dig = malloc((a->n + 1) * sizeof(char));
    mult.sign = a->sign;
    for (i = 0; i < a->n; i++) {
        pre =(unsigned char)(a->dig[i] * 2 + over);
        if (pre >=100) {
            over = 1;
            mult.dig[i] = (char)(pre - 100);
        } else {
            mult.dig[i] = pre;
            over = 0;
        }
    }

    mult.n = a->n;
    if (over == 1) {
        mult.dig[a->n] = over;
        mult.n++;
    }
    return mult;
}

LongN div2(LongN * a) {
    LongN div;
    int i = 0;
    char over = 0;

    div.dig = malloc((a->n) * sizeof(char));
    div.sign = a->sign;
    for (i = a->n-1; i >= 0; i--) {
        div.dig[i] =(char)((a->dig[i] + over * 100) / 2);
        if ((a->dig[i] + over * 100) % 2 != 0) {
            over = 1;
        } else
            over = 0;
    }

    div.n = a->n;

    if (div.n != 1) {
        for (i = div.n; div.dig[i - 1] == 0; i--);
        div.dig = realloc(div.dig, i * sizeof(char));
        div.n = i;
    }

    return div;
}

LongN multLN(LongN a, LongN b) {
    char ost;
    LongN mult;
    LongN * max = maxLN(&a, &b);
    LongN * min = minLN(&a, &b);
    LongN  maxu = copyLN(max);
    LongN  minu = copyLN(min);
    mult.dig = malloc(sizeof(char));
    mult.n = 1;
    mult.dig[0] = 0;
    if (max->sign == min->sign)
        mult.sign = 0;
    else
        mult.sign = 1;
    while ((minu.n != 1) || (minu.dig[0] != 0)) {
        ost = (char)(minu.dig[0] % 2);
        if (ost == 1)
            mult = sumLN(mult, maxu);
        minu = div2(&minu);
        maxu = mult2(&maxu);
    }
    free(maxu.dig);
    free(minu.dig);
    return mult;
}

LongN divLN(LongN a, LongN b) {
    int i = 0;
    int j = 0;
    int q = 0;
    char * new = malloc(200 * sizeof(char));
    LongN div;
    LongN mnog;
    LongN dif;
    LongN res;
    LongN * max = maxLN(&a, &b);
    LongN * min = minLN(&a, &b);
    LongN  maxu = copyLN(max);
    LongN  minu = copyLN(min);

    // проверка на ноль
    if (maxu.dig[maxu.n - 1] == 0 || minu.dig[minu.n - 1] == 0) {
        div.dig = NULL;
        div.sign = 2;
        div.n = 0;
        return div;
    }

    int lenmax = 0;
    int lenmin = 0;

    if (maxu.sign == minu.sign)
        new[q] = '+';
    else
        new[q] = '-';
    q++;

    minu.sign = 0;
    maxu.sign = 0;

    if (minu.dig[minu.n - 1] / 10 == 0) {
        lenmin = 1 + (minu.n - 1) * 2;
    } else {
        lenmin = minu.n * 2;
    }
    if (maxu.dig[maxu.n - 1] / 10 == 0) {
        lenmax = 1 + (maxu.n - 1) * 2;
    } else {
        lenmax = maxu.n * 2;
    }

    lenmax -= lenmin;
    char * str = malloc((lenmax + 2) * sizeof(char));
    str[0] = '1';
    for (i = 1; i <= lenmax; i++) {
        str[i] = '0';
    }
    str[i] = '\0';
    for (j = 0; j <= lenmax; j++) {
        mnog = getLongN(str);
        dif = multLN(mnog, minu);
        dif.sign = 1;
        i = 1;
        res = sumLN(maxu, dif);
        while (res.sign != 1) {
            i++;
            free(maxu.dig);
            maxu = copyLN(&res);
            free(res.dig);
            res = sumLN(maxu, dif);
        }
        i--;
        free(res.dig);


        new[q] = (char) (i + '0');
        q++;
        str[strlen(str) - 1] = '\0';
        free(mnog.dig);
        free(dif.dig);
    }
    new[q] = '\0';
    div = getLongN(new);
    free(str);
    free(new);
    return div;
}

LongN powLN (LongN * a, int power) {
    LongN res;
    // проверка степень
    if (power < 0) {
        res.dig = malloc(sizeof(char));
        res.dig[0] = 0;
        res.sign = 0;
        res.n = 1;
        return res;
    }
    if (power == 0) {
        res.dig = malloc(sizeof(char));
        res.dig[0] = 1;
        res.sign = 0;
        res.n = 1;
        return res;
    }
    int i;
    res = copyLN(a);
    LongN help;
    for (i = 1; i < power; i++) {
        help = multLN(res, *a);
        free(res.dig);
        res = copyLN(&help);
        free(help.dig);
    }
    return res;
}

