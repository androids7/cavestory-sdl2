#include <string>
#include "animated_sprite.h"
#include "first_cave_bat.h"
#include "graphics.h"

const units::Frame kNumFlyFrames{3};
const units::FPS kFlyFps{13};
const units::AngularVelocity kAngularVelocity{120.0 / 1000.0};
const units::Game kMoveAmplitude{units::tileToGame(5) / 2.0};

const std::string kSpritePath{"content/NpcCemet.bmp"};

FirstCaveBat::FirstCaveBat(Graphics& graphics, Vector<units::Game> pos) :
    pos_(pos),
    center_y_{pos_.y},
    facing_{Facing::RIGHT},
    flight_angle_{0.0},
    sprites_()
{
    initializeSprites(graphics);
}

FirstCaveBat::~FirstCaveBat() {}

void FirstCaveBat::draw(Graphics& graphics) const
{
    sprites_.at(getSpriteState())->draw(graphics, pos_);
}

void FirstCaveBat::update(const std::chrono::milliseconds elapsed_time,
        const units::Game player_x)
{
    flight_angle_ += kAngularVelocity * elapsed_time.count();

    facing_ = pos_.x + units::tileToGame(1) / 2.0 > player_x
        ? Facing::LEFT
        : Facing::RIGHT;

    const auto angle = std::sin(units::degreesToRadians(flight_angle_));
    pos_.y = center_y_ + units::tileToGame(5) / 2.0 * units::Game(angle);
    sprites_[getSpriteState()]->update(elapsed_time);
}

const Rectangle FirstCaveBat::getDamageRectangle() const
{
    return Rectangle(
            pos_.x + units::tileToGame(1) / 2.0,
            pos_.y + units::tileToGame(1) / 2.0,
            0,
            0);
}

void FirstCaveBat::initializeSprites(Graphics& graphics)
{
    for (int facing = (int)Facing::FIRST_FACING;
            facing < (int)Facing::LAST_FACING;
            ++facing) {
        initializeSprite(graphics, SpriteState(Facing(facing)));
    }
}

void FirstCaveBat::initializeSprite(Graphics& graphics,
        const SpriteState& sprite_state)
{
    auto tile_y = sprite_state.facing == Facing::RIGHT ? 3 : 2;
    sprites_[sprite_state] = std::shared_ptr<Sprite>(new AnimatedSprite{
            graphics,
            kSpritePath,
            units::tileToPixel(2), units::tileToPixel(tile_y),
            units::tileToPixel(1), units::tileToPixel(1),
            kFlyFps, kNumFlyFrames
            });
}

const FirstCaveBat::SpriteState FirstCaveBat::getSpriteState() const
{
    return SpriteState(facing_);
}