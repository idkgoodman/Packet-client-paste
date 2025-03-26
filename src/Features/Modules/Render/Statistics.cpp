//
// Created by alteik on 02/10/2024.
//

#include "Statistics.hpp"
#include <SDK/Minecraft/ClientInstance.hpp>
#include <SDK/Minecraft/Network/PacketID.hpp>
#include <Features/Events/PacketInEvent.hpp>
#include <Features/Events/BaseTickEvent.hpp>
#include <SDK/Minecraft/Network/Packets/TextPacket.hpp>
#include <Hook/Hooks/RenderHooks/D3DHook.hpp>
#include "NameProtect.hpp"
#include <spdlog/spdlog.h>
#include <ImRenderUtils.hpp>
#include <ColorUtils.hpp>
#include <FontHelper.hpp>

std::vector<std::string> gamemodesToGetStatsFor = {
    "sky", "sky-duos", "sky-squads", "sky-mega",
    "ctf", "bed", "bed-duos", "bed-squads",
    "sg", "sg-duos"
};

int Statistics::mKills = 0;
int Statistics::mPlayTime = 0;
bool Statistics::mShouldUpdate = false;

void Statistics::resetStatistics() {
    mKills = 0;
    mPlayTime = 0;
}

void Statistics::makeRequestsForAllGamemodes(const std::string& gamertag) {
    resetStatistics();

    for (const auto& gamemode : gamemodesToGetStatsFor) {
        auto request = std::make_unique<HttpRequest>(
            HttpMethod::GET,
            "https://api.playhive.com/v0/game/all/" + gamemode + "/" + gamertag,
            "",
            "",
            &Statistics::onHttpResponse,
            this
        );
        int64_t now = NOW;
        mRequests.emplace_back(now, std::move(request));
    }
}

void Statistics::onHttpResponse(HttpResponseEvent event) {
    auto sender = static_cast<Statistics*>(event.mSender);

    if (event.mStatusCode == 200) {
        nlohmann::json json = nlohmann::json::parse(event.mResponse);

        int kills = 0, deaths = 0, played = 0;

        if (json.contains("kills")) {
            kills = json["kills"];
        }
        if (json.contains("deaths")) {
            deaths = json["deaths"];
        }
        if (json.contains("played")) {
            played = json["played"];
        }

        mKilss += kills;
        mPlayTime += played;

    } else if (event.mStatusCode == 404) {
        spdlog::info("[Statistics] Stats not found for this gamemode!");
    } else {
        spdlog::error("[Statistics] Request failed with status code: {}", event.mStatusCode);
    }

    mCompletedRequests++;

    if (mCompletedRequests == gamemodesToGetStatsFor.size()) {
        mShouldUpdate = false;
    }
}

void Statistics::onEnable() {
    resetStatistics();
    gFeatureManager->mDispatcher->listen<BaseTickEvent, &Statistics::onBaseTickEvent>(this);
    gFeatureManager->mDispatcher->listen<RenderEvent, &Statistics::onRenderEvent>(this);
    mElement->mVisible = true;
}

void Statistics::onDisable() {
    gFeatureManager->mDispatcher->deafen<BaseTickEvent, &Statistics::onBaseTickEvent>(this);
    gFeatureManager->mDispatcher->deafen<RenderEvent, &Statistics::onRenderEvent>(this);
    mElement->mVisible = false;
}

void Statistics::onRenderEvent(RenderEvent& event) {
    if (!ClientInstance::get()->getLocalPlayer()) return;
    if (!ClientInstance::get()->getLevelRenderer()) return;

    if (!mShouldUpdate) {
        kills = mKills;
        played = mPlayTime;
    }

    std::string
        mKillsStr = "Kills " + std::to_string(kills);
        mPlayTimeStr = "Play Time " + std::to_string(played);

    ) pos = mElement->getPos();

    auto drawList = ImGui::GetForegroundDrawList();

    ImVec2 size = ImVec2(200, 105);

    ImVec4 area = ImVec4(pos.x, pos.y, pos.x + size.x, pos.y + size.y);
    ImRenderUtils::addBlur(area, 4.f, 4.f, drawList, false);
    drawList->AddRectFilled(pos, ImVec2(area.z, area.w), ImColor(0.f, 0.f, 0.f, 0.5), 10.0f);
    drawList->AddShadowRect(ImVec2(pos.x - 3, pos.y - 3), ImVec2(area.z + 3, area.w + 3), ImColor(0.f, 0.f, 0.f, 1.f), 50.f, ImVec2(0, 0));
    ImVec2 titlePos = pos;
    titlePos.x += 64;
    titlePos.y += 3.8;

    ImVec2 lineStart = ImVec2(pos.x, pos.y + 30);
    ImVec2 lineEnd = ImVec2(pos.x + 200, pos.y + 33);

    int lineLength = 20;
    int lengthPerLine = 200 / lineLength;

    // Рисуем линии с эффектом свечения
    for (int i = 0; i < lineLength; i++) {
        ImVec2 point = ImVec2(lineStart.x + (lineEnd.x - lineStart.x) * i / lineLength, lineStart.y);

        // Light factor для изменения интенсивности свечения
        float lightFactor = (float)i / lineLength;
        ImU32 lineColor = ColorUtils::getThemedColor(i);

        ImVec4 color = ImColor(lineColor);

        // Увеличиваем яркость в зависимости от lightFactor для свечения
        color.x *= (0.5f + 0.5f * lightFactor);  // Красный канал
        color.y *= (0.5f + 0.5f * lightFactor);  // Зеленый канал
        color.z *= (0.5f + 0.5f * lightFactor);  // Синий канал

        // Рисуем несколько линий с разными смещениями для эффекта свечения
        for (int j = -2; j <= 2; ++j) {
            // Смещаем линию по оси X и Y для эффекта свечения
            float offset = j * 0.5f;  // Смещение для свечения
            ImGui::GetWindowDrawList()->AddLine(
                ImVec2(lineStart.x + offset, lineStart.y + offset),
                ImVec2(lineEnd.x + offset, lineEnd.y + offset),
                ImColor(color),
                3.0f);  // Толщина линии
        }

        // Основная линия с обычным цветом
        ImGui::GetWindowDrawList()->AddLine(lineStart, lineEnd, ImColor(lineColor), 3.0f);
    }

        drawList->AddRectFilled(point, ImVec2(point.x + lengthPerLine, lineEnd.y), ImColor(color));
    }

    int startPadding = 38;
    FontHelper::pushPrefFont(true);

    ImRenderUtils::drawShadowText(drawList, "Statistics", titlePos, ImColor(255, 255, 255, 255), 22.f, false);
    ImRenderUtils::drawShadowText(drawList, mKillsStr, ImVec2(pos.x + 10, pos.y + startPadding), ImColor(255, 255, 255, 255), 20, false);
    ImRenderUtils::drawShadowText(drawList, mDeathsStr, ImVec2(pos.x + 10, pos.y + startPadding + 20), ImColor(255, 255, 255, 255), 20, false);
    ImRenderUtils::drawShadowText(drawList, mGamesPlayedStr, ImVec2(pos.x + 10, pos.y + startPadding + 40), ImColor(255, 255, 255, 255), 20, false);

    FontHelper::popPrefFont();
}

void Statistics::onBaseTickEvent(BaseTickEvent& event) {
    auto player = event.mActor;
    if (!player) return;

    if (NOW < lastUpdate + 15000 && !mShouldUpdate) {
        mShouldUpdate = false;
        return;
    } else if (!mShouldUpdate && NOW > lastUpdate + 15000) {
        mShouldUpdate = true;
        makeRequestsForAllGamemodes(mPlayerName);
        lastUpdate = NOW;
    }

    auto nameProtect = gFeatureManager->mModuleManager->getModule<NameProtect>();
    if (nameProtect->mEnabled) {
        mPlayerName = nameProtect->mOldLocalName;
    } else {
        mPlayerName = player->getLocalName();
    }

    for (auto it = mRequests.begin(); it != mRequests.end();) {
        if (it->second->isDone()) {
            it = mRequests.erase(it);
        } else {
            ++it;
        }
    }

    if (!mRequests.empty()) {
        auto& request = mRequests.front();
        if (!request.second->mRequestSent) {
            request.second->sendAsync();
        }
    }
}