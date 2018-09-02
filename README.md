# Stature

<p align="center">
  <img src="./stat.jpg" width="256" />
</p>

## Get Started

Run `yarn add stature` and add `"stature"` to your BuckleScript dependencies list in `bsconfig.json`.

## Using the Library

```reason
open BsReactNative;

/* configuring your store */
module CounterConfig = {
  type t = int;
  let debugName = "Counter";
  let value = 0;
};

/* creating your store */
module CounterStore = Stature.CreateStore(CounterConfig);

/* accessing state in ui */
<CounterStore.Consumer
  render=(
    state =>
    <View>
      <Text>
        (ReasonReact.stringToElement(string_of_int(state)))
      </Text>
      <Button onPress=(() => CounterStore.updateState(Some(state + 1)) label="Increment Counter" />
    </View>
  )
/>

/* accessing state outside of a Consumer */
let oneUpped = CounterStore.state^ + 1;
```
