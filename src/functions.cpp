#include "../include/functions.h"
#include "../include/structures.h"
#include <iostream>
#include <string>
#include <iomanip>

std::ostream& operator<<(std::ostream& os, const Speciality& speciality) {
  switch (speciality) {
    case INFORMATIONAL_SYSTEMS_AND_TECHNOLOGIES: os << "INFORMATIONAL_SYSTEMS_AND_TECHNOLOGIES"; break;
    case MATHEMATICS: os << "MATHEMATICS"; break;
    case PEDAGOGY: os << "PEDAGOGY"; break;
  }
  return os;
}

std::istream& operator>>(std::istream& is, Speciality& speciality) {
  int value;
  is >> value;
  speciality = static_cast<Speciality>(value);
  return is;
}

using namespace std;

void Create(Student *s, const int N)
{
  int speciality;

  for (int i = 0; i < N; i++)
  {
    cout << "Студент № " << i + 1 << ":" << endl;
    cin.get();
    cin.sync();
    cout << " прізвище: "; getline(cin, s[i].surname);
    cout << " курс: "; cin >> s[i].studying_year;
    cout << " спеціальність: "; cin >> speciality;
    s[i].speciality = (Speciality)speciality;
    cout << " оцінка з фізики: "; cin >> s[i].physics_mark;
    cout << " оцінка з математики: "; cin >> s[i].maths_mark;
    cout << " оцінка з предмету спеціальності(";

    switch (s[i].speciality) {
      case INFORMATIONAL_SYSTEMS_AND_TECHNOLOGIES:
        cout << "програмування): "; cin >> s[i].SpecialityGrade.programming_mark;

      break;

      case MATHEMATICS:
        cout << "чисельні методи): "; cin >> s[i].SpecialityGrade.numerical_methods_mark;
      break;

      case PEDAGOGY:
        cout << "педагогіка): "; cin >> s[i].SpecialityGrade.pedagogy_mark;
      break;
    }

    cout << endl;
  }
}

void Print(Student *s, const int N) {
  cout << "===================================================================================================================================================================\n";
  cout << "|   № | Прізвище     | Курс  | Спеціальність                           | Оц(Фізика) | Оц(Математика) | Оц(Програмування) | Оц(Чисельні методи) | Оц(Педагогіка)   |\n";
  cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
  for (int i = 0; i < N; i++) {
    cout << "| " << setw(3) << right << i + 1 << " ";
    cout << "| " << setw(22) << left << s[i].surname
         << " | " << setw(4) << right << s[i].studying_year << " "
         << " | " << setw(40) << left << s[i].speciality
         << "| " << setw(10) << right << s[i].physics_mark << " "
         << "| " << setw(14) << right << s[i].maths_mark << " "
         << "| " << setw(17) << right << (s[i].speciality == INFORMATIONAL_SYSTEMS_AND_TECHNOLOGIES ? to_string(s[i].SpecialityGrade.programming_mark) : "-") << " "
         << "| " << setw(19) << right << (s[i].speciality == MATHEMATICS ? to_string(s[i].SpecialityGrade.numerical_methods_mark) : "-") << " "
         << "| " << setw(17) << right << (s[i].speciality == PEDAGOGY ? to_string(s[i].SpecialityGrade.pedagogy_mark) : "-") << "|"
         << endl;
  }
  cout << "===================================================================================================================================================================\n";
}

float CountAverageMark(Student *s, int i) {
  switch (s[i].speciality) {
    case INFORMATIONAL_SYSTEMS_AND_TECHNOLOGIES:
      return (s[i].physics_mark + s[i].maths_mark + s[i].SpecialityGrade.programming_mark) / 3.0;
    case MATHEMATICS:
      return (s[i].physics_mark + s[i].maths_mark + s[i].SpecialityGrade.numerical_methods_mark) / 3.0;
    case PEDAGOGY:
      return (s[i].physics_mark + s[i].maths_mark + s[i].SpecialityGrade.pedagogy_mark) / 3.0;
  }
  return 0;
}

void Sort(Student *s, const int N)
{
  Student tmp;
  for (int i0 = 0; i0 < N - 1; i0++) {
    for (int i1 = 0; i1 < N - i0 - 1; i1++) {
      if ((CountAverageMark(s, i1) < CountAverageMark(s, i1 + 1)) ||
          (CountAverageMark(s, i1) == CountAverageMark(s, i1 + 1) && s[i1].speciality > s[i1 + 1].speciality) ||
          (CountAverageMark(s, i1) == CountAverageMark(s, i1 + 1) && s[i1].speciality == s[i1 + 1].speciality && s[i1].surname > s[i1 + 1].surname)) {
        tmp = s[i1];
        s[i1] = s[i1 + 1];
        s[i1 + 1] = tmp;
          }
    }
  }
}

int *IndexSort(Student *s, const int N)
{
  int *I = new int[N];
  for (int i=0; i<N; i++)
    I[i]=i;
  int i, j, value;
  for (i = 1; i < N; i++)
  {
    value = I[i];
    for (j = i - 1;
    j >= 0 && ((CountAverageMark(s, j) < CountAverageMark(s, j + 1)) ||
          (CountAverageMark(s, j) == CountAverageMark(s, j + 1) && s[j].speciality > s[j + 1].speciality) ||
          (CountAverageMark(s, j) == CountAverageMark(s, j + 1) && s[j].speciality == s[j + 1].speciality && s[j].surname > s[j + 1].surname)) ;
    j--)
    {
      I[j + 1] = I[j];
    }
    I[j + 1] = value;
  }
  return I;
}

void PrintIndexSorted(Student *s, int *I, const int N) {
  cout << "===================================================================================================================================================================\n";
  cout << "|   № | Прізвище     | Курс  | Спеціальність                           | Оц(Фізика) | Оц(Математика) | Оц(Програмування) | Оц(Чисельні методи) | Оц(Педагогіка)   |\n";
  cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
  for (int i = 0; i < N; i++) {
    cout << "| " << setw(3) << right << i + 1 << " ";
    cout << "| " << setw(22) << left << s[I[i]].surname
         << " | " << setw(4) << right << s[I[i]].studying_year << " "
         << " | " << setw(40) << left << s[I[i]].speciality
         << "| " << setw(10) << right << s[I[i]].physics_mark << " "
         << "| " << setw(14) << right << s[I[i]].maths_mark << " "
         << "| " << setw(17) << right << (s[I[i]].speciality == INFORMATIONAL_SYSTEMS_AND_TECHNOLOGIES ? to_string(s[I[i]].SpecialityGrade.programming_mark) : "-") << " "
         << "| " << setw(19) << right << (s[I[i]].speciality == MATHEMATICS ? to_string(s[I[i]].SpecialityGrade.numerical_methods_mark) : "-") << " "
         << "| " << setw(17) << right << (s[I[i]].speciality == PEDAGOGY ? to_string(s[I[i]].SpecialityGrade.pedagogy_mark) : "-") << "|"
         << endl;
  }
  cout << "===================================================================================================================================================================\n";
}

int BinSearch(Student *p, const int N, const string surname, const float average_mark, const int speciality)
{
  int left = 0, right = N - 1, middle;
  while (left <= right)
  {
    middle = (left + right) / 2;
    float middleAverageMark = CountAverageMark(p, middle);
    if (p[middle].surname == surname && middleAverageMark == average_mark && p[middle].speciality == speciality)
      return middle;
    if (p[middle].surname > surname || (p[middle].surname == surname && middleAverageMark > average_mark) || (p[middle].surname == surname && middleAverageMark == average_mark && p[middle].speciality > speciality))
      right = middle - 1;
    else
      left = middle + 1;
  }
  return -1;
}