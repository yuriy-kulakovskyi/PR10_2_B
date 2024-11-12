#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
#include <iostream>

enum Speciality {
  INFORMATIONAL_SYSTEMS_AND_TECHNOLOGIES,
  MATHEMATICS,
  PEDAGOGY
};

std::istream& operator>>(std::istream& is, Speciality& speciality);
std::ostream& operator<<(std::ostream& os, const Speciality& speciality);

struct Student {
  std::string surname;
  int studying_year;
  Speciality speciality;
  int physics_mark;
  int maths_mark;
  union {
    int programming_mark;
    int numerical_methods_mark;
    int pedagogy_mark;
  } SpecialityGrade;
};

#endif // STRUCTURES_H