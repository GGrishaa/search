#!/usr/bin/env python3
import csv
import random
import sys


male_first = [
    'Ivan', 'Petr', 'Alexey', 'Dmitriy', 'Sergey', 'Mihail', 'Andrew', 
    'Vladimir', 'Nikolas', 'Alex', 'Denis', 'Evgen', 'Max', 
    'Roman', 'Artem', 'Viktor', 'Konstantin', 'Oleg', 'Pavel', 'Stanislav', 
    'Ruslan', 'Gregory', 'Boris', 'Gleb', 'Igor', 'Leonid', 'Vadim', 'Yuri', 
    'Anatoly', 'Valentin', 'Vitaly', 'Timur', 'Rinat', 'Eduard', 'Arkady', 
    'Stepan', 'Fedor', 'Yaroslav', 'Vladislav', 'Vyacheslav', 'Abram', 'Adam', 
    'Albert', 'Alfred', 'Anton', 'Arnold', 'Arseny', 'Bogdan', 'Bronislav',
    'Valery', 'Veniamin', 'Vladlen', 'Vsevolod', 'Gennady', 'Georgy', 'German', 
    'David', 'Daniel', 'Egor', 'Emil', 'Erast', 'Efim', 'Zakhar', 'Ignat', 'Ilya', 
    'Innocent', 'Joseph', 'Kazimir', 'Karl', 'Kirill']
  
female_first = [
    'Ann', 'Maria', 'Lana', 'Olga', 'Tat', 'Irina', 'Natalia', 
    'Svetlana', 'Ekaterina', 'Julia', 'Viktoria', 'Dar', 'Elizabeth', 
    'Anastasya', 'Kristina', 'Marina', 'Oksana', 'Inna', 'Ludmila', 
    'Galina', 'Alina', 'Valeria', 'Veronika', 'Vera', 'Nadezhda', 
    'Lyubov', 'Zoya', 'Raisa', 'Tamara', 'Ella', 'Nina', 'Polina', 
    'Sofia', 'Ulyana', 'Yana', 'Larisa', 'Alla', 'Zhanna', 'Ada', 
    'Adelina', 'Aza', 'Alevtina', 'Alexandra', 'Angelina', 'Antonina', 
    'Ariadna', 'Bella', 'Bronislava', 'Valentina', 'Vanda', 'Varvara',
    'Vasilisa', 'Diana', 'Eva', 'Zinaida', 'Inessa', 'Kapitolina', 'Karina',
    'Kira', 'Claudia', 'Lada', 'Lydia', 'Lilia', 'Lora', 'Maya', 
    'Margarita', 'Martha', 'Milan']


surnames = [
    'Ivanov', 'Petrov', 'Sidorov', 'Kozlov', 'Smirnov', 'Vasilev', 'Popov', 'Nikiforov', 'Mironov',
    'Morozov', 'Volkov', 'Fedorov', 'Sokolov', 'Mihaylov', 'Novikov', 'Kiselev', 
    'Kuznetsov', 'Golubev', 'Lebedev', 'Zaytsev', 'Toporkov',
    'Bikov', 'Makarov', 'Nikolaev', 'Orlov', 'Pavlov', 'Romanov', 'Savelev', 'Lvov', 
    'Baranov', 'Belov', 'Vinogradov', 'Gromov', 'Egorov', 'Karpov', 'Krylov', 'Lapin', 
    'Melnikov', 'Naumov', 'Nesterov', 'Panov', 'Rogov', 'Rybakov', 'Samsonov', 'Tikhonov', 
    'Ustinov', 'Filatov', 'Fomin', 'Shcherbakov', 'Yakovlev', 'Mazitov', 'Yarigin', 'Andreev',
    'Lukoyanov', 'Danilov', 'Osipov', 'Kazakov', 'Bakeev', 'Alihanov', 'Galitsin', 'Goltsev', 
    'Guskov', 'Irkov', 'Klepikov', 'Kolbasov', 'Konovalov', 'Osipenkov', 'Pochinov', 'Rakov',
    'Sirotkon', 'Starodubtsev', 'Timohin', 'Trofimov', 'Zhuravlev', 'Bolotnikov', 'Firsov',
    'Agenosov', 'Busarev', 'Abramov', 'Avdeev', 'Agafonov', 'Akimov', 'Aksenov', 'Alekseev', 
    'Anisimov', 'Antipov', 'Antonov', 'Arkhipov', 'Astafyev', 'Afanasyev', 'Baranov', 'Belov', 
    'Belozerov', 'Belyaev', 'Biryukov', 'Blokhin', 'Bobrov', 'Bobylev', 'Bogdanov', 'Borisov', 
    'Bragin', 'Budanov', 'Burov', 'Bykov', 'Vasiliev', 'Vinogradov', 'Volkov', 'Vorobyov',
    'Gavrilov', 'Galkin', 'Gerasimov', 'Glazkov', 'Glebov', 'Golovanov', 'Gorbunov', 'Gordeev', 'Gorin', 'Gorshkov',
    'Goryachev', 'Grebenshchikov', 'Grigoriev', 'Gromov', 'Gusev', 'Davydov', 'Dementyev', 'Demidov', 'Denisov', 'Dmitriev',
    'Doroshenko', 'Drozdov', 'Dubov', 'Evdokimov', 'Evseev', 'Eliseev', 'Eremenko', 'Efimov', 'Efremov', 'Zhukov',
    'Zhuravlev', 'Zaitsev', 'Zakharov', 'Zelenov', 'Zimin', 'Zotov', 'Zykov', 'Ignatiev', 'Ilyin', 'Isaev',
    'Kazakov', 'Kalashnikov', 'Kalinin', 'Kapustin', 'Kasyanov', 'Klimov', 'Klyuev', 'Kovalev', 'Kolpakov', 'Komarov',
    'Kondratiev', 'Kopylov', 'Korneev', 'Korolev', 'Korshunov', 'Kostin', 'Kotov', 'Koshkin', 'Krasnov', 'Kudryavtsev']


male_patr = ['Ivanovich', 'Petrovich', 'Alexeevich', 'Dmitrievich', 'Sergeevich', 
             'Mihailovich', 'Andreevich', 'Vladimirovich', 'Nikolaevich', 
             'Alexandrovich', 'Borisovich', 'Grigorievich', 'Egorovich', 'Ilyich', 
             'Kirillovich', 'Leonidovich', 'Olegovich', 'Ruslanovich', 'Stanislavovich', 
             'Timofeevich', 'Fedorovich', 'Yurievich', 'Abramovich', 'Adamovich', 
             'Albertovich', 'Alfredovich', 'Anatolievich', 'Antonovich', 'Arkadievich',
             'Bogdanovich', 'Bronislavovich', 'Vadimovich', 'Valentinovich', 'Valerievich', 
             'Venediktovich', 'Viktorovich', 'Vilenovich', 'Vladlenovich', 'Vladislavovich', 
             'Vsevolodovich', 'Gennadievich', 'Georgievich']


female_patr = ['Ivanovna', 'Petrovna', 'Alexeevna', 'Dmitrievna', 'Sergeevna', 
               'Mihaylovna', 'Andreevna', 'Vladimirovna', 'Nikolaevna', 
               'Alexandrovna', 'Borisovna', 'Grigorievna', 'Egorovna', 
               'Ilinichna', 'Kirillovna', 'Leonidovna', 'Olegovna', 
               'Ruslanovna', 'Stanislavovna', 'Timofeevna', 'Fedorovna', 'Yurievna', 
               'Abramovna', 'Adamovna', 'Albertovna', 'Alfredovna', 'Anatolievna', 'Antonovna', 'Arkadievna',
               'Bogdanovna', 'Bronislavovna', 'Vadimovna', 'Valentinovna', 'Valerievna', 'Venediktovna',
               'Viktorovna', 'Vilenovna', 'Vladlenovna', 'Vladislavovna', 'Vsevolodovna', 'Gennadievna', 'Georgievna']


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
        return f"{surname}a {first} {patr}"


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
        writer.writerow(['home_number', 'flat_number', 'room_count', 
                         'square', 'name', 'vilagers_count'])
        writer.writerows(data)


if __name__ == "__main__":
    main()
