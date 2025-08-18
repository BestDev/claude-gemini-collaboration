# Sounds Directory

This directory is prepared for future sound effects and background music.

## Planned Sound Effects

The game architecture supports adding these sounds in future versions:

- **Line clear sound** (`clear.wav`)
- **Game over sound** (`gameover.wav`)
- **Piece drop sound**
- **Piece rotation sound**
- **Level up sound**
- **Tetris (4-line clear) sound**
- **Background music**

## Audio Format

SFML supports various audio formats including:
- WAV (recommended for sound effects)
- OGG (recommended for music)
- FLAC
- MP3 (limited support)

## Implementation Notes

To add sound support:

1. Extend the `Renderer` class or create a separate `AudioManager` class
2. Load sound buffers and create sound instances
3. Call appropriate play() methods during game events
4. Consider adding volume controls and mute options

## License Considerations

Ensure any audio files comply with their licenses for your distribution method.