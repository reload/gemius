<?php

/**
 * Implementation of hook_admin_settings() for configuring the module
 */
function gemius_admin_settings_form(&$form_state) {
  $form['account'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
    '#collapsible' => FALSE,
  );

  $form['account']['gemius_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Gemius identifier'),
    '#default_value' => variable_get('gemius_key', ''),
    '#size' => 30,
    '#maxlength' => 30,
    '#required' => TRUE,
    '#description' => t('The identifier'),
  );

  // Page specific visibility configurations.
  $form['page_vis_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Page specific tracking settings'),
    '#collapsible' => false,
    /*'#collapsed' => TRUE,*/
  );

  $pages = variable_get('gemius_pages', '');
  $description = t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>'));
  
  $form['page_vis_settings']['gemius_pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Pages to be excluded from statistics'),
    '#default_value' => $pages,
    '#description' => $description,
    '#wysiwyg' => FALSE,
  );
  
    // Render the role overview.
  $form['role_vis_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Role specific tracking settings'),
    '#collapsible' => false,
  );

  $roles = user_roles();
  $role_options = array();
  foreach ($roles as $rid => $name) {
    $role_options[$rid] = $name;
  }
  $form['role_vis_settings']['gemius_roles'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Add tracking for specific roles'),
    '#default_value' => variable_get('gemius_roles', array()),
    '#options' => $role_options,
    '#description' => t('Add tracking only for the selected role(s). If none of the roles are selected, all users will be tracked. If a user has any of the roles checked, that user will be tracked.'),
  );

  return system_settings_form($form);
}