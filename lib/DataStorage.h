#pragma once
#include <fstream>
#include <iostream>
#include "Utils.h"

/**
 * @author Иван Городков & Павел Городков
 * @version 1.0.0
 * @date 22.12.2021
 * Структура предоставляет композицию всех
 * необходимых данных для инициализации состояния игры,
 * а также содержит маркер наличия сохранений.
 */
struct RawData {
    size_t row_count;
    size_t col_count;
    std::vector<bool> store;
    bool game_saved;

    /**
     * Конструктор
     * @param _row_count   высота поля
     * @param _col_count   ширина поля
     * @param _store       вектор состояния ячеек
     * @param _game_saved  флаг сохранённой версии игры
     */
    RawData(
            size_t _row_count,
            size_t _col_count,
            const std::vector<bool> _store,
            bool _game_saved = true
    ) :
        row_count(_row_count),
        col_count(_col_count),
        store(_store),
        game_saved(_game_saved)
    {}
};

/**
 * @author Иван Городков & Павел Городков
 * @version 1.0.0
 * @date 22.12.2021
 * @see VectorUtils
 * @see RawData
 * Класс, реализующий функционал сохранения и загрузки игры
 * Хранит путь до файла с сохранённой игрой, управляет потоками ввода/вывода
 * для записи сеанса игры в файл
 */
class DataStorage {
    static std::string data_path;
    static std::ifstream input;
    static std::ofstream output;

public:
    /**
     * @method Сохранение текущего сеанса игры
     * @param data
     */
    static void saveGame(const RawData& data) {
        output.open(data_path, std::ios::out);
        output << data.row_count << ' ';
        output << data.col_count << ' ';
        output << VectorUtils::serialize(data.store);
        output.close();
    }

    /**
     * @method Метод для загрузки сохранённой игры
     * @return RawData instance
     */
    static RawData loadGame() {
        size_t row_count;
        size_t col_count;
        std::vector<bool> store;
        bool game_saved;

        try {
            std::string raw_store;
            input.open(data_path, std::ios::in);
            input >> row_count;
            input >> col_count;
            input >> raw_store;
            store = VectorUtils::deserialize(raw_store);
            game_saved = true;
        } catch (std::exception& ex) {
            std::cerr << ex.what() << std::endl;
            game_saved = false;
        }
        input.close();

        return RawData(row_count, col_count, store, game_saved);
    }
};

std::string DataStorage::data_path = "../storage/raw.data";
std::ifstream DataStorage::input = std::ifstream();
std::ofstream DataStorage::output = std::ofstream();