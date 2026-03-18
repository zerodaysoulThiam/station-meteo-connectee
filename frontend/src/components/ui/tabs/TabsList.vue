<script setup lang="ts">
import { TabsList } from "radix-vue"
</script>

<template>
  <TabsList class="inline-flex items-center rounded-lg bg-muted p-1 gap-1">
    <slot />
  </TabsList>
</template>
