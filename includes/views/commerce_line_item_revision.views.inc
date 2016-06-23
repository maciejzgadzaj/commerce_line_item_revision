<?php

/**
 * Provide Line Item revision Views integration.
 */

/**
 * Implements hook_views_data_alter().
 */
function commerce_line_item_revision_views_data_alter(&$data) {
  $data['commerce_line_item']['table']['default_relationship'] = array(
    'commerce_line_item_revision' => array(
      'table' => 'commerce_line_item_revision',
      'field' => 'revision_id',
    ),
  );
}

/**
 * Implements hook_views_data()
 */
function commerce_line_item_revision_views_data() {
  $data = array();

  $data['commerce_line_item_revision']['table']['entity type'] = 'commerce_line_item';
  $data['commerce_line_item_revision']['table']['group']  = t('Commerce Line Item revision');

  // Advertise this table as a possible base table.
  $data['commerce_line_item_revision']['table']['base'] = array(
    'field' => 'revision_id',
    'title' => t('Commerce Line Item revision'),
    'help' => t('Commerce Line Item revision is a history of changes to a line item.'),
    'defaults' => array(
      'field' => 'revision_id',
    ),
  );

  $data['commerce_line_item_revision']['table']['join'] = array(
    'commerce_line_item' => array(
      'left_field' => 'revision_id',
      'field' => 'revision_id',
    )
  );

  $data['commerce_line_item_revision']['table']['default_relationship'] = array(
    'commerce_line_item' => array(
      'table' => 'commerce_line_item',
      'field' => 'revision_id',
    ),
  );

  // Expose the revision line item ID.
  $data['commerce_line_item_revision']['line_item_id'] = array(
    'title' => t('Line Item ID', array(), array('context' => 'a drupal commerce line item')),
    'help' => t('The unique internal identifier of the line item.'),
    'field' => array(
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'commerce_line_item_handler_argument_line_item_line_item_id',
      'numeric' => TRUE,
      'validate type' => 'line_item_id',
    ),
  );

  // Expose the revision ID.
  $data['commerce_line_item_revision']['revision_id'] = array(
    'title' => t('Revision ID'),
    'help' => t('The revision ID of the line item revision.'),
    'field' => array(
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'commerce_line_item',
      'base field' => 'revision_id',
      'title' => t('Line Item'),
      'label' => t('Latest line item revision'),
    ),
  );

  // Expose the line item revision user ID.
  $data['commerce_line_item_revision']['revision_uid'] = array(
    'title' => t('User'),
    'help' => t('Relate a line item revision to the user who created the revision.'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'base field' => 'uid',
      'field' => 'revision_uid',
      'field_name' => 'revision_uid',
      'label' => t('Revision user'),
    ),
  );


  // Expose the type-dependent line item title.
  $data['commerce_line_item_revision']['line_item_title'] = array(
    'field' => array(
      'title' => t('Title'),
      'help' => t('The title of this line item revision determined by its type.'),
      'handler' => 'commerce_line_item_revision_handler_field_line_item_title',
    ),
  );

  // Expose the line item revision label.
  $data['commerce_line_item_revision']['line_item_label'] = array(
    'title' => t('Label'),
    'help' => t('The label of this line item revision.'),
    'field' => array(
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Expose the line item revision quantity.
  $data['commerce_line_item_revision']['quantity'] = array(
    'title' => t('Quantity'),
    'help' => t('The quantity of this line item revision.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
      'float' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  // Expose the line item revision log message.
  $data['commerce_line_item_revision']['log'] = array(
    'title' => t('Log message'),
    'help' => t('The log message entered when the revision was created.'),
    'field' => array(
      'handler' => 'views_handler_field_xss',
     ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  // Expose the line item revision timestamp.
  $data['commerce_line_item_revision']['revision_timestamp'] = array(
    'title' => t('Revision date'),
    'help' => t('The date the line item revision was created.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  return $data;
}
