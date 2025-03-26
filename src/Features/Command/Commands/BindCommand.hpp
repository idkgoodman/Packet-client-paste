#pragma once
//
// Created by leha 20.03.2025
//

#include <Solstice.hpp>
#include <Features/FeatureManager.hpp>
#include "spdlog/spdlog.h"

class BindCommand : public Command {
public:
    BindCommand() : Command("bind") {}
    void execute(const std::vector<std::string>& args) override;
    [[nodiscard]] std::vector<std::string> getAliases() const override;
    [[nodiscard]] std::string getDescription() const override;
    [[nodiscard]] std::string getUsage() const override;
};