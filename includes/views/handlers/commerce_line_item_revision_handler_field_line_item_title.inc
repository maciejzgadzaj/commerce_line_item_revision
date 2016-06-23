<?php

/**
 * @file
 * Definition of commerce_line_item_revision_handler_field_line_item_title.
 */

/**
 * Field handler to return a line item revision's title.
 *
 * @ingroup views_field_handlers
 */
class commerce_line_item_revision_handler_field_line_item_title extends views_handler_field {
  /**
   * {@inheritdoc}
   */
  function construct() {
    parent::construct();

    $this->additional_fields['revision_id'] = 'revision_id';
  }

  /**
   * {@inheritdoc}
   */
  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  /**
   * {@inheritdoc}
   */
  function render($values) {
    // Load the line item and return its title.
    $revision_id = $this->get_value($values, 'revision_id');
    $line_item = entity_revision_load('commerce_line_item', $revision_id);
    return commerce_line_item_title($line_item);
  }
}
