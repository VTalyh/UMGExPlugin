# UMGExPlugin
UMG Extension plugin for UE4.

UMG is great. UMG also annoys me greatly sometimes. I took that annoyance and made a plugin that speeds up my workflow greatly.

I'm open sourcing it hoping that maybe someone in the community will add more cool widget types and functionality. I still have some planned functionality that doesn't exist yet, I am building functionality as I need it. I'm hoping others will extend on to this as well.

# Features:
* Widget Lists - Create lists of buttons, sliders, choice selectors easily
* TableView - Create a table list view thing easily
* Improved Panel Switching - Widgets not active are destroyed, child widgets are aware of parent. Makes menu navigation *really* easy
* Radio Scroller Widget - Its like a radio group and a drop down merged together
* Tag System - All widgets have labels and tags. Easier to consolidate events.
* Container Event Wrappers - Container widgets such as WidgetLists offer simplified events for their children so you don't need 10 button press events if you have 10 buttons. Just one event to handle all buttons, even if buttons are added at runtime.
* Improved Runtime Widget Manipulation - Add widgets to things at runtime better with things like Widget Lists and other small improvements throughout
* Improved Widget Propagation - Can skin, re-layout, and change functionality of widget classes and they'll propagate correctly and easily

# Warning 
Currently only supports being built from source. Only tested on latest promoted branch. It should work with 4.6.1 but I haven't tried it. I plan to support official releases after the official 4.7 release.

# Demo
Now here is a really long video that could be super condensed but I was livestreaming so... yeah. If its not available in 1080p, its still processing.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=YGBpKE0NKfg" target="_blank"><img src="http://img.youtube.com/vi/YGBpKE0NKfg/0.jpg" width="240" height="180" border="10" /></a>
