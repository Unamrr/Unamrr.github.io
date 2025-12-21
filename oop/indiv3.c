class Car {
    private String number;
    private String marka;
    private int probeg;
    private double price;
    private int year;
    private double obDvig;

    public Car(String number, String marka, int probeg, double price, int year, double obDvig) {
        this.number = number;
        this.marka = marka;
        this.probeg = probeg;
        this.price = price;
        this.year = year;
        this.obDvig = obDvig;
    }

    //содержит ли номер четные цифры
    public boolean hasEvenDigits() {
        for (char c : number.toCharArray()) {
            if (c >= '0' && c <= '9') {
                int digit = c - '0';
                if (digit != 0 && digit % 2 == 0) {
                    return true; // есть четные цифры
                }
            }
        }
        return false; // нет четных цифр
    }

    //находится ли объем в диапазоне
    public boolean isVolumeInRange(double min, double max) {
        return obDvig >= min && obDvig <= max;
    }

    public String getMarka() {
        return marka;
    }

    @Override
    public String toString() {
        return "Номер: " + number + ", Марка: " + marka + ", Пробег: " + probeg +
                ", Цена: " + price + ", Год: " + year + ", Объем: " + obDvig;
    }
}

/*Задачa на ArrayList
Даны сведения об автомобилях: номер, марка, пробег, цена, год выпуска, объем двигателя. Вывести без повторений марки автомобилей, номер которых не содержит чёт
ных цифр, а объем принадлежит заданному диапазон*/

import java.util.ArrayList;
import java.util.List;

public class CarProcessor {
    public static void main(String[] args) {
        // Создаем список автомобилей
        List<Car> cars = new ArrayList<>();

        // Добавляем тестовые данные (без имен параметров!)
        cars.add(new Car("A123BC", "Toyota", 50000, 1500000, 2018, 2.0));
        cars.add(new Car("B776XX", "BMW", 30000, 2500000, 2020, 2.0));
        cars.add(new Car("C135DF", "Toyota", 80000, 1200000, 2015, 1.6));
        cars.add(new Car("D579GH", "Mercedes", 40000, 3000000, 2019, 1.5));
        cars.add(new Car("E111JK", "Audi", 60000, 2200000, 2017, 3.0));
        cars.add(new Car("F333LM", "BMW", 20000, 2800000, 2021, 3.0));
        cars.add(new Car("G555NP", "Honda", 90000, 900000, 2014, 2.8));
        cars.add(new Car("H777QR", "Toyota", 100000, 800000, 2013, 2.6));
        cars.add(new Car("I999ST", "Lexus", 25000, 3200000, 2022, 2.5));
        cars.add(new Car("J135UV", "Audi", 35000, 2400000, 2019, 1.4));

        // Заданный диапазон объема двигателя
        double minVolume = 1.5;
        double maxVolume = 2.9;

        System.out.println("Все автомобили:");
        System.out.println("=========================================");
        for (Car car : cars) {
            System.out.println(car);
        }

        
        System.out.println("\nМарки автомобилей, у которых номер не содержит четных цифр, объем двигателя от " +
                minVolume + " до " + maxVolume);
        
        ArrayList<String> uniqueBrands = new ArrayList<>();

        for (Car car : cars) {
            // номер НЕ содержит четных цифр И объем в диапазоне
            if (!car.hasEvenDigits() && car.isVolumeInRange(minVolume, maxVolume)) {
                String marka = car.getMarka();

                // нет ли уже такой марки в списке
                if (!uniqueBrands.contains(marka)) {
                    uniqueBrands.add(marka);
                }
            }
        }

        if (uniqueBrands.isEmpty()) {
            System.out.println("Нет таких автомобилей.");
        } else {
            System.out.println();
            for (int i = 0; i < uniqueBrands.size(); i++) {
                System.out.println((i + 1) + ". " + uniqueBrands.get(i));
            }
        }
    }
}
