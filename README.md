# Discord Rich Presence

## Building/Installing
### 1. Installing with windows
It's the easiest way, just download installator [here](https://github.com/minot0r/discord-rich-presence-command-line/tree/master/win-setup) (also works portable)
Windows compiled version has been wrapped into a installator with NSIS

### 2. Compiling
First compile Discord Rich Presence C++ Lib [here](https://discordapp.com/developers/docs/rich-presence/how-to)
And download rapidJSON library [rapidJSON library](https://github.com/Tencent/rapidjson)
Put the include files into path `include/rapidjson` (according to [jsonwrapper.cpp](https://github.com/minot0r/discord-rich-presence-command-line/blob/master/jsonwrapper.cpp))
Then use any compiler you want (I'm using g++)
And compile all the code with the lib built before.

## Usage
### Getting around
The program is split with commands, which are : presence, timer, party, image, changeid, config, clear, reset

### Presence
Change presence text

### Timer
#### Start
Start to the actual timestamp

#### End
Stop in X minutes given by user

### Party
Follow given usage

### Image
Change image, to the given image name set in discordapp.com/developers/application/your_app

### Config
View actual config

### Clear
Clear console text

### Reset
Reset DRPC's config


## More infos
[here](https://discordapp.com/developers/docs/rich-presence/how-to)


