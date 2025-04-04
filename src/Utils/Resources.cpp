// This file is generated by CMake. Do not edit it manually.
#include "Resources.hpp"
#include "FontHelper.hpp"
#include <imgui.h>

void ResourceLoader::loadResources() {
    ImFontConfig font_config;
    font_config.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_NoHinting;
    auto cash_wav = GET_RESOURCE(cash_wav);
    Resources.emplace("cash.wav", cash_wav);
    auto cash_register_sound_wav = GET_RESOURCE(cash_register_sound_wav);
    Resources.emplace("cash_register_sound.wav", cash_register_sound_wav);
    auto celestial_off_wav = GET_RESOURCE(celestial_off_wav);
    Resources.emplace("celestial_off.wav", celestial_off_wav);
    auto celestial_on_wav = GET_RESOURCE(celestial_on_wav);
    Resources.emplace("celestial_on.wav", celestial_on_wav);
    auto fard_wav = GET_RESOURCE(fard_wav);
    Resources.emplace("fard.wav", fard_wav);
    auto fonts_Comfortaa_Bold_ttf = GET_RESOURCE(fonts_Comfortaa_Bold_ttf);
    Resources.emplace("comfortaa_bold", fonts_Comfortaa_Bold_ttf);
    FontHelper::Fonts.emplace("comfortaa_bold", ImGui::GetIO().Fonts->AddFontFromMemoryTTF(fonts_Comfortaa_Bold_ttf.data2(), fonts_Comfortaa_Bold_ttf.size(), 20, &font_config));
    FontHelper::Fonts.emplace("comfortaa_bold_large", ImGui::GetIO().Fonts->AddFontFromMemoryTTF(fonts_Comfortaa_Bold_ttf.data2(), fonts_Comfortaa_Bold_ttf.size(), 42, &font_config));
    auto fonts_Comfortaa_ttf = GET_RESOURCE(fonts_Comfortaa_ttf);
    Resources.emplace("comfortaa", fonts_Comfortaa_ttf);
    FontHelper::Fonts.emplace("comfortaa", ImGui::GetIO().Fonts->AddFontFromMemoryTTF(fonts_Comfortaa_ttf.data2(), fonts_Comfortaa_ttf.size(), 20, &font_config));
    FontHelper::Fonts.emplace("comfortaa_large", ImGui::GetIO().Fonts->AddFontFromMemoryTTF(fonts_Comfortaa_ttf.data2(), fonts_Comfortaa_ttf.size(), 42, &font_config));
    auto fonts_Mojangles_Bold_ttf = GET_RESOURCE(fonts_Mojangles_Bold_ttf);
    Resources.emplace("mojangles_bold", fonts_Mojangles_Bold_ttf);
    FontHelper::Fonts.emplace("mojangles_bold", ImGui::GetIO().Fonts->AddFontFromMemoryTTF(fonts_Mojangles_Bold_ttf.data2(), fonts_Mojangles_Bold_ttf.size(), 20, &font_config));
    FontHelper::Fonts.emplace("mojangles_bold_large", ImGui::GetIO().Fonts->AddFontFromMemoryTTF(fonts_Mojangles_Bold_ttf.data2(), fonts_Mojangles_Bold_ttf.size(), 42, &font_config));
    auto fonts_Mojangles_ttf = GET_RESOURCE(fonts_Mojangles_ttf);
    Resources.emplace("mojangles", fonts_Mojangles_ttf);
    FontHelper::Fonts.emplace("mojangles", ImGui::GetIO().Fonts->AddFontFromMemoryTTF(fonts_Mojangles_ttf.data2(), fonts_Mojangles_ttf.size(), 20, &font_config));
    FontHelper::Fonts.emplace("mojangles_large", ImGui::GetIO().Fonts->AddFontFromMemoryTTF(fonts_Mojangles_ttf.data2(), fonts_Mojangles_ttf.size(), 42, &font_config));
    auto fonts_Open_Sans_Bold_ttf = GET_RESOURCE(fonts_Open_Sans_Bold_ttf);
    Resources.emplace("open_sans_bold", fonts_Open_Sans_Bold_ttf);
    FontHelper::Fonts.emplace("open_sans_bold", ImGui::GetIO().Fonts->AddFontFromMemoryTTF(fonts_Open_Sans_Bold_ttf.data2(), fonts_Open_Sans_Bold_ttf.size(), 20, &font_config));
    FontHelper::Fonts.emplace("open_sans_bold_large", ImGui::GetIO().Fonts->AddFontFromMemoryTTF(fonts_Open_Sans_Bold_ttf.data2(), fonts_Open_Sans_Bold_ttf.size(), 42, &font_config));
    auto fonts_Open_Sans_ttf = GET_RESOURCE(fonts_Open_Sans_ttf);
    Resources.emplace("open_sans", fonts_Open_Sans_ttf);
    FontHelper::Fonts.emplace("open_sans", ImGui::GetIO().Fonts->AddFontFromMemoryTTF(fonts_Open_Sans_ttf.data2(), fonts_Open_Sans_ttf.size(), 20, &font_config));
    FontHelper::Fonts.emplace("open_sans_large", ImGui::GetIO().Fonts->AddFontFromMemoryTTF(fonts_Open_Sans_ttf.data2(), fonts_Open_Sans_ttf.size(), 42, &font_config));
    auto fonts_Product_Sans_Bold_ttf = GET_RESOURCE(fonts_Product_Sans_Bold_ttf);
    Resources.emplace("product_sans_bold", fonts_Product_Sans_Bold_ttf);
    FontHelper::Fonts.emplace("product_sans_bold", ImGui::GetIO().Fonts->AddFontFromMemoryTTF(fonts_Product_Sans_Bold_ttf.data2(), fonts_Product_Sans_Bold_ttf.size(), 20, &font_config));
    FontHelper::Fonts.emplace("product_sans_bold_large", ImGui::GetIO().Fonts->AddFontFromMemoryTTF(fonts_Product_Sans_Bold_ttf.data2(), fonts_Product_Sans_Bold_ttf.size(), 42, &font_config));
    auto fonts_Product_Sans_ttf = GET_RESOURCE(fonts_Product_Sans_ttf);
    Resources.emplace("product_sans", fonts_Product_Sans_ttf);
    FontHelper::Fonts.emplace("product_sans", ImGui::GetIO().Fonts->AddFontFromMemoryTTF(fonts_Product_Sans_ttf.data2(), fonts_Product_Sans_ttf.size(), 20, &font_config));
    FontHelper::Fonts.emplace("product_sans_large", ImGui::GetIO().Fonts->AddFontFromMemoryTTF(fonts_Product_Sans_ttf.data2(), fonts_Product_Sans_ttf.size(), 42, &font_config));
    auto fonts_SF_Pro_Display_Bold_ttf = GET_RESOURCE(fonts_SF_Pro_Display_Bold_ttf);
    Resources.emplace("sf_pro_display_bold", fonts_SF_Pro_Display_Bold_ttf);
    FontHelper::Fonts.emplace("sf_pro_display_bold", ImGui::GetIO().Fonts->AddFontFromMemoryTTF(fonts_SF_Pro_Display_Bold_ttf.data2(), fonts_SF_Pro_Display_Bold_ttf.size(), 20, &font_config));
    FontHelper::Fonts.emplace("sf_pro_display_bold_large", ImGui::GetIO().Fonts->AddFontFromMemoryTTF(fonts_SF_Pro_Display_Bold_ttf.data2(), fonts_SF_Pro_Display_Bold_ttf.size(), 42, &font_config));
    auto fonts_SF_Pro_Display_ttf = GET_RESOURCE(fonts_SF_Pro_Display_ttf);
    Resources.emplace("sf_pro_display", fonts_SF_Pro_Display_ttf);
    FontHelper::Fonts.emplace("sf_pro_display", ImGui::GetIO().Fonts->AddFontFromMemoryTTF(fonts_SF_Pro_Display_ttf.data2(), fonts_SF_Pro_Display_ttf.size(), 20, &font_config));
    FontHelper::Fonts.emplace("sf_pro_display_large", ImGui::GetIO().Fonts->AddFontFromMemoryTTF(fonts_SF_Pro_Display_ttf.data2(), fonts_SF_Pro_Display_ttf.size(), 42, &font_config));
    auto fonts_Sarabun_Light_ttf = GET_RESOURCE(fonts_Sarabun_Light_ttf);
    Resources.emplace("sarabun_light", fonts_Sarabun_Light_ttf);
    FontHelper::Fonts.emplace("sarabun_light", ImGui::GetIO().Fonts->AddFontFromMemoryTTF(fonts_Sarabun_Light_ttf.data2(), fonts_Sarabun_Light_ttf.size(), 20, &font_config));
    FontHelper::Fonts.emplace("sarabun_light_large", ImGui::GetIO().Fonts->AddFontFromMemoryTTF(fonts_Sarabun_Light_ttf.data2(), fonts_Sarabun_Light_ttf.size(), 42, &font_config));
    auto fonts_Tenacity_Icons_ttf = GET_RESOURCE(fonts_Tenacity_Icons_ttf);
    Resources.emplace("tenacity_icons", fonts_Tenacity_Icons_ttf);
    FontHelper::Fonts.emplace("tenacity_icons", ImGui::GetIO().Fonts->AddFontFromMemoryTTF(fonts_Tenacity_Icons_ttf.data2(), fonts_Tenacity_Icons_ttf.size(), 20, &font_config));
    FontHelper::Fonts.emplace("tenacity_icons_large", ImGui::GetIO().Fonts->AddFontFromMemoryTTF(fonts_Tenacity_Icons_ttf.data2(), fonts_Tenacity_Icons_ttf.size(), 42, &font_config));
    auto mariodeath_wav = GET_RESOURCE(mariodeath_wav);
    Resources.emplace("mariodeath.wav", mariodeath_wav);
    auto nursultan_off_wav = GET_RESOURCE(nursultan_off_wav);
    Resources.emplace("nursultan_off.wav", nursultan_off_wav);
    auto nursultan_on_wav = GET_RESOURCE(nursultan_on_wav);
    Resources.emplace("nursultan_on.wav", nursultan_on_wav);
    auto seven_days_png = GET_RESOURCE(seven_days_png);
    Resources.emplace("seven_days.png", seven_days_png);
    auto skinblinker_txt = GET_RESOURCE(skinblinker_txt);
    Resources.emplace("skinblinker.txt", skinblinker_txt);
    auto smooth_off_wav = GET_RESOURCE(smooth_off_wav);
    Resources.emplace("smooth_off.wav", smooth_off_wav);
    auto smooth_on_wav = GET_RESOURCE(smooth_on_wav);
    Resources.emplace("smooth_on.wav", smooth_on_wav);
    auto windows_background_wav = GET_RESOURCE(windows_background_wav);
    Resources.emplace("windows_background.wav", windows_background_wav);
}
