#ifndef FLAT_HPP
#define FLAT_HPP

#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

using namespace std;

/**
 * @file flat.hpp
 * @brief Реализация класса квартиры согласно варианту в ЛР1
 */

/**
 * @brief Класс квартиры
 *
 * Хранит информацию о номере дома, квартиры, количестве комнат,
 * площади, владельце и числе проживающих. Перегружает операторы
 * сравнения для распределения в структурах поиска по ключу.
 */

class flat {
 public:
  /**
   * @brief Конструктор с параметрами
   * @param home_n Номер дома
   * @param flat_n Номер квартиры
   * @param room_c Количество комнат
   * @param s Общая площадь
   * @param owner ФИО владельца
   * @param vil_c Число проживающих
   */
  flat(long home_n = 0, long flat_n = 0, long room_c = 0, double s = 0,
       string owner = "", long vil_c = 0);
  /**
   * @brief Конструктор копирования
   * @param other Исходный объект
   */
  flat(const flat& other);
  /**
   * @brief Деструктор
   */
  ~flat() = default;
  /**
   * @brief Оператор "меньше" для сравнения объектов
   *
   * Сравнивает исключительно по ключу
   * @param other Другая квартира для сравнения
   * @return true если текущая квартира меньше другой, иначе false
   */
  bool operator<(const flat& other) const;
  /**
   * @brief Оператор "больше"
   *
   * Ситуация текущий объект больше другого равносильна ситуации другой объект
   * меньше текущего
   * @param other Другая квартира для сравнения
   * @return true если текущая квартира больше другой, иначе false
   */
  bool operator>(const flat& other) const;
  /**
   * @brief Оператор "больше или равен"
   *
   * Ситуация текущий объект больше или равен другому противоположна ситуации
   * текущий объект меньше другого
   * @param other Другая квартира для сравнения
   * @return true если текущая квартира больше или равна другой, иначе false
   */
  bool operator>=(const flat& other) const;
  /**
   * @brief Оператор "меньше или равен"
   *
   * Ситуация текущий объект меньше или равен другому противоположна ситуации
   * текущий объект больше другого
   * @param other Другая квартира для сравнения
   * @return true если текущая квартира меньше или равна другой, иначе false
   */
  bool operator<=(const flat& other) const;
  /**
   * @brief Оператор присваивания
   *
   * Правила присваивания:
   * 1. Поля инициализируются значениями, равными соответствующим значением
   * полей другого объекта
   * 2. Возваращается ссылка на текущий объект
   * @param other Другая квартира
   * @return ссылка на текущий объект
   */
  flat& operator=(const flat& other);
  /**
   * @brief Оператор "не равен"
   *
   * Если значение хотя бы одного поля не совпадает, то объекты не равны
   * @param other Другая квартира для сравнения
   * @return true если текущая квартира не равна другой, иначе false
   */
  bool operator!=(const flat& other) const;
  /**
   * @brief Оператор "равенства со строкой"
   *
   * Проверяет соответствие с ключом
   * @param other Ключ-строка
   * @return true если текущая квартира соответствует указанному ключу, иначе
   * false
   */
  bool operator==(const string& owner) const;
  /**
   * @brief Получение ключа
   *
   * Возвращает строковый ключ объекта, который является ФИО владельца квартиры
   * @return ФИО владельца
   */
  string get_owner() const;

  /**
   * @brief Оператор вывода в поток
   *
   * Формат вывода стандартный, как и формат записи в .csv файлах
   * @param f объект квартиры
   * @return ссылка на тот же поток os для цепочечных вызовов
   */
  friend ostream& operator<<(ostream& os, const flat& f);

 private:
  long home_n_;   ///< Номер дома
  long flat_n_;   ///< Номер квартиры
  long room_c_;   ///< Количество комнат
  double s_;      ///< Общая площадь квартиры
  string owner_;  ///< ФИО владельца
  long vil_c_;    ///< Количество проживающих в квартире
};

/**
 * @brief Вывод массива квартир
 *
 * Построчно печатает данные о квартирах в массиве
 * @param flats указатель на начало массива квартир
 * @param size размер массива
 * @param os поток вывода
 */
void print_flats(flat* flats, size_t size, ostream& os);

/**
 * @brief Чтение массива данных о квартирах из файла
 *
 * @param filename имя файла
 * @param size размер массива (передается по ссылке)
 */
flat* load_from_csv(const string filename, size_t& size);

/**
 * @brief Проверка корректности поиска массивов
 *
 * Поэлементно сравнивает два массива одинакового размера
 * @param flats1 указатель на первый элемент первого массива
 * @param flats2 указатель на первый элемент второго массива
 * @param size размер массивов
 * @return true если массивы в точности совпадают, иначе false
 */
bool check_correct(flat* flats1, flat* flats2, size_t size);

#endif