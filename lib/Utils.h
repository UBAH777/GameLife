#pragma once
#include <string>
#include <vector>
#include <functional>

/**
 * @author Иван Городков & Павел Городков
 * @version 1.0.0
 * @date 22.12.2021
 * Предоставляет методы сериализации
 * и десериализации вектора.
 */
class VectorUtils {
public:
    /**
     * Переводит вектор состояния ячеек в строку
     * @param vector raw store
     * @return string representation
     */
    static std::string serialize(const std::vector<bool>& vector) {
        return convert<std::vector<bool>, std::string>(vector);
    }

    /**
     * Переводит строку информации о сохранённой игре в вектор состояния ячеек
     * @param string data
     * @return vector<bool> store
     */
    static std::vector<bool> deserialize(const std::string& string) {
        return convert<std::string, std::vector<bool>>(string);
    }

private:
    /**
     * Конвертер итерируемых сущностей
     * @tparam FromType
     * @tparam ToType
     * @param object
     * @return converted entity
     */
    template <typename FromType, typename ToType>
    static ToType convert(const FromType& object) {
        ToType result;
        for (const auto& item : object) {
            result.push_back(item);
        }
        return result;
    }
};