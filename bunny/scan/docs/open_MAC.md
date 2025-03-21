# Wi-Fi MAC layer

ESP32s Wi-Fi MAC (Media Access Control) layer is currently closed source (duh). But some people have figured this [as in here](https://github.com/esp32-open-mac/esp32-open-mac). How'd they reverse engineer this man!

## The idea

There are a lot of things we can do once we figure this data layer out. These features weren't documented properly by espressif but we can use them to send raw Wi-Fi data (so maybe even deauth frames?)


> Firstly what is the MAC layer?

Its basically a huge support block for Wi-Fi that allows it provide some async data service (It'll be interesting to know why async here). IEEE 802.11 defines two MAC sub-layers:

1. Distributed Coordination Function
2. Point Coordination Function

Their meanings can be found easily on google. 


# References

MAC Layer: https://www.geeksforgeeks.org/ieee-802-11-mac-frame/
