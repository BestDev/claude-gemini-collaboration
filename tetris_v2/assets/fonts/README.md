# Fonts Directory

This directory should contain font files for the game. The game will attempt to load `arial.ttf` from this directory.

## Font Requirements

- The game expects a TrueType font file (.ttf)
- Default expected filename: `arial.ttf`
- If no font is found, the game will use the system default font

## Adding Fonts

To add a font file:

1. Obtain a suitable TrueType font (ensure you have the right to use it)
2. Rename it to `arial.ttf` or modify the code in `Renderer.cpp` to use your filename
3. Place it in this directory

## License Considerations

Please ensure any fonts you add comply with their respective licenses. For distribution, you may need to:

- Use open source fonts (like those from Google Fonts)
- Purchase commercial licenses
- Use system fonts that are already available on target platforms

## Recommended Free Fonts

Some good free alternatives that work well for games:

- **DejaVu Sans** - Open source, excellent readability
- **Liberation Sans** - Metric-compatible with Arial
- **Open Sans** - Modern, clean appearance
- **Roboto** - Good for UI elements

Download from Google Fonts or their respective repositories.