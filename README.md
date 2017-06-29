# Vanilla 2D Engine
-------------------

A simple C++ visual novel engine

## Getting Started

Vanilla2D is very simple visual novel engine (currently, **without** labels/different roots support) which is created to implement basic one-root stories with some dynamic elements. Features:

* Easy scripting language syntax

* Background, music, font change

* Unicode text support

* Basic animations (fade in/out)

### Download binaries and game template: 

[v1.0.0](https://github.com/MrOnlineCoder/Vanilla2D/releases/tag/v1.0.0)

## Project structure

A Vanilla2D game/project is just a folder with all assets inside.
To run a game, put that folder right next to the main executable and run it with -game argument:

```
vanilla2d -game <assets folder>
```

Every game folder can contain:

* img folder (all game images)

* fonts folder (all game fonts)

* music folder (all music tracks)

And next three files are **required**:

* app.vanilla2d - game configuration

* script.vanilla2d - game script itself

* fonts/script.ttf - default script font

## Configuring

app.vanilla2d contains some confugration for game itself.

It is a key-value file, example:

```
# comments starting with # are ignored

# Game window width
width = 1024

# Game window height
height = 728

# Application title
title = Test

# FPS limit
fps = 60

```

script.vanilla2d is actual game script, which **contains** statements, separated by new line. There are some available statements, which can be used in a script:

* bg <filename> - changes background. <filename> is target image filename, **relative** to img folder. (Example: if you have intro.png background in img folder, then statement must look like **bg intro.png**).

* music <filename> - changes playing music. <filename> is target music filename, **relative** to music folder. (Note: MP3 is not supported)

* txt <text> - shows text to user.

* text_color <red> <green> <blue> <alpha> - changes text color, where red, green, blue, alpha are integers between 0 and 255, which represent RGBA color.

* delay <amount> - delays script execution for <amount> milliseconds (text will be also hidden)

* font <filename> - changes current font. <filename> - target font filename, relative to **fonts** folder

* fade <in/out> <speed> - creates fading animation. The most balanced value of <speed> is 5.

**Note: script.vanilla2d must be saved in UTF-8 encoding to work properly** 

### See "game" folder for working example.
 
## Contributing

If you found a bug/security issue/typo error, feel free to create an issue!

Pull requests are also welcomed.

## Authors

* [MrOnlineCoder](https://github.com/MrOnlineCoder)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

## Acknowledgments

* SFML Library by SFML Team

* Foaly for SettingsParser class - [GitHub](https://github.com/SFML/SFML/wiki/Source:-Settings-Parser)

* BarrensZeppelin for FPS counter class - [GitHub](https://github.com/SFML/SFML/wiki/Source:-FPS)
