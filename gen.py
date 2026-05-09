#!/usr/bin/env python3
import csv
import random
import sys


male_first = [
    'Иван', 'Петр', 'Алексей', 'Дмитрий', 'Сергей', 'Михаил', 'Андрей', 
    'Владимир', 'Николай', 'Александр', 'Денис', 'Евгений', 'Максим', 
    'Роман', 'Артем', 'Виктор', 'Константин', 'Олег', 'Павел', 'Станислав', 'Руслан', 'Григорий'
]
  
female_first = [
    'Анна', 'Мария', 'Елена', 'Ольга', 'Татьяна', 'Ирина', 'Наталья', 
    'Светлана', 'Екатерина', 'Юлия', 'Виктория', 'Дарья', 'Елизавета', 
    'Анастасия', 'Кристина', 'Марина', 'Оксана', 'Инна', 'Людмила', 'Галина'
]


surnames = [
    'Иванов', 'Петров', 'Сидоров', 'Козлов', 'Смирнов', 'Васильев', 'Попов', 'Никифоров', 'Миронов',
    'Морозов', 'Волков', 'Федоров', 'Соколов', 'Михайлов', 'Новиков', 'Киселев',
    'Федоров', 'Кузнецов', 'Голубев', 'Морозов', 'Лебедев', 'Зайцев', 'Топорков',
    'Быков', 'Макаров', 'Николаев', 'Орлов', 'Павлов', 'Романов', 'Савельев', 'Львов'
]


male_patr = ['Иванович', 'Петрович', 'Алексеевич', 'Дмитриевич', 'Сергеевич', 
             'Михайлович', 'Андреевич', 'Владимирович', 'Николаевич', 
             'Александрович']


female_patr = ['Ивановна', 'Петровна', 'Алексеевна', 'Дмитриевна', 'Сергеевна', 
               'Михайловна', 'Андреевна', 'Владимировна', 'Николаевна', 
               'Александровна']


def generate_fio():
    is_male = random.choice([True, False])
    
    if is_male:
        first = random.choice(male_first)
        patr = random.choice(male_patr)
        surname = random.choice(surnames)
        return f"{surname} {first} {patr}"
    else:
        first = random.choice(female_first)
        patr = random.choice(female_patr)
        surname = random.choice(surnames)
        return f"{surname}а {first} {patr}"


def main():
    if len(sys.argv) != 2:
        return

    n_records = int(sys.argv[1])
    filename = f"CSV/apartments_{n_records}.csv"

    data = []

    for _ in range(n_records):
        home = random.randint(1, 50)
        flat_num = random.randint(1, 1000)
        rooms = random.randint(1, 6)
        area = round(random.uniform(35.0, 160.0), 1)
        residents = random.randint(1, rooms + 2)
        fio = generate_fio()

        data.append([home, flat_num, rooms, area, fio, residents])

    random.shuffle(data)

    with open(filename, 'w', newline='', encoding='utf-8') as f:
        writer = csv.writer(f, delimiter=';', quoting=csv.QUOTE_MINIMAL)
        writer.writerow(['номер_дома', 'номер_квартиры', 'количество_комнат', 
                         'площадь', 'ФИО_владельца', 'число_проживающих'])
        writer.writerows(data)


if __name__ == "__main__":
    main()
