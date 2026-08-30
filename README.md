# Mario Superstar Baseball - Character Cloning & Native Texture Decoupling

Standalone modding toolkit and technical guide for cloning characters and decoupling native CMPR textures in *Mario Superstar Baseball* (USA GYQE01, GameCube).

## Technical Guide
For the complete technical breakdown, see **[CHARACTER_CLONING_GUIDE.md](CHARACTER_CLONING_GUIDE.md)**.

## Quick Start
```bash
# Clone Donkey Kong onto Luigi (Slot 1) with selective Blue fur tint:
python3 tools/patch_character_v6.py \
  --source-iso orig/GYQE01.iso \
  --target-iso "Mario_Superstar_Baseball_Mod.iso" \
  --target-slot 1 \
  --source-slot 2 \
  --hue 0.60
```
