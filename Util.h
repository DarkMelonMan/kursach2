#pragma once

/// <summary>
/// Перечисление типов стихийного урона: нестихийный, огонь, магия и молния
/// </summary>

enum Element {
	none, fire, magic, lighting
};

/// <summary>
/// Перечисление типов существ: живые существа, монстр и игрок
/// </summary>

enum EntityType {
	living, monster, player
};

/// <summary>
/// Строковые определния перечисления element
/// </summary>

static const char* elementNames[] = {
	"none", "fire", "magic", "lighting"
};

/// <summary>
/// Строковые определния перечисления entity
/// </summary>

static const char* entityTypes[] = {
	"living", "monster", "player"
};
