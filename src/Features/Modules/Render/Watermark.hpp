#ifndef WATERMARK_HPP
#define WATERMARK_HPP

#include <string>
#include "Interface.hpp"  // Для доступа к интерфейсу и шрифтам
#include "FontHelper.hpp" // Для помощи с шрифтами
#include "ColorUtils.hpp" // Для получения цвета темы
#include <imgui.h>
#include <Module.hpp>

class Watermark : public ModuleBase<Watermark> {
public:
    enum class Mode {
        Packet
    };

    // Настройки
    BoolSetting mGlow = BoolSetting("Glow", "Whether or not use glow");
    BoolSetting mBoldText = BoolSetting("Bold Text", "Whether or not use bold text");
    BoolSetting mShowVersion = BoolSetting("Show Version", "Whether or not show version");
    BoolSetting mShowClient = BoolSetting("Show Client", "Whether or not add client text to the Packet text");

    // Конструктор класса
    Watermark() : ModuleBase("Watermark", "A Packet client's watermark", ModuleCategory::Render, false) {
        // Добавляем настройки
        addSetting(&mGlow);
        addSetting(&mBoldText);
        addSetting(&mShowVersion);
        addSetting(&mShowClient);

        // Инициализация имени модуля
        mNames = {
            {Lowercase, "watermark"},
            {LowercaseSpaced, "watermark"},
            {Normal, "Watermark"},
            {NormalSpaced, "Watermark"}
        };
    }

    ~Watermark() = default;

    // Устанавливает режим отображения
    void SetMode(Mode mode);

    // Включает или отключает подсветку текста
    void SetGlow(bool enable);

    // Включает или отключает использование жирного шрифта
    void SetBoldText(bool disabled);

    // Включает или отключает отображение версии проекта
    void SetShowVersion(bool enable);

    // Включает или отключает отображение клиента
    void SetShowClient(bool disabled);

    // Обновляет отображение водяного знака
    void Update();

private:
    Mode currentMode;           // Текущий режим (Packet или PacketClient)
    bool glowEnabled;           // Подсветка
    bool boldTextDisabled;      // Жирный текст
    bool showVersionEnabled;    // Отображение версии
    bool showClientDisabled;    // Отображение клиента

    // Функция для получения шрифта с использованием FontHelper
    FontHelper* GetFont();

    // Функция для получения цвета темы
    ImVec4 GetThemeColor();

    // Функция для отображения текста
    void RenderWatermark(const std::string& text, const ImVec4& color, FontHelper* font);

    // Массив с именами модуля
    std::vector<std::pair<std::string, std::string>> mNames;
};

#endif // WATERMARK_HPP