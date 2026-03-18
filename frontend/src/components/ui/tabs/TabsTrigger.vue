<script setup lang="ts">
import { TabsTrigger, type TabsTriggerProps } from "radix-vue"

const props = defineProps<TabsTriggerProps>()
</script>

<template>
  <TabsTrigger
    v-bind="props"
    class="inline-flex items-center justify-center whitespace-nowrap rounded-md px-4 py-1.5 text-sm font-medium text-muted-foreground ring-offset-background transition-all focus-visible:outline-none focus-visible:ring-2 focus-visible:ring-ring focus-visible:ring-offset-2 disabled:pointer-events-none disabled:opacity-50 data-[state=active]:bg-card data-[state=active]:text-foreground data-[state=active]:shadow-sm"
  >
    <slot />
  </TabsTrigger>
</template>
