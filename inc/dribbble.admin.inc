<?php
/**
 *  @file
 *  Admin form builders for Dribbble module.
 */

/**
 *  Form builder callback for admin/config/media/dribbble.
 */
function dribbble_admin() {

  $form = array();

  $form['cache_length'] = array(
    '#type' => 'textfield',
    '#title' => t('Cache Length'),
    '#description' => t('Enter the amount of hours that cached data should be kept.')
  );

  return $form;

}