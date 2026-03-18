<script setup lang="ts">
import { TabsContent, type TabsContentProps } from "radix-vue"

const props = defineProps<TabsContentProps>()
</script>

<template>
  <TabsContent v-bind="props" class="mt-6 focus-visible:outline-none">
    <slot />
  </TabsContent>
</template>
