<?php

/**
 * @file
 * Provides the Google No CAPTCHA administration settings.
 */

/**
 * Form callback; administrative settings for Google No CAPTCHA.
 */
function recaptcha_admin_settings() {
  // Load the recaptcha library. Error if library does not load.
  if (!_recaptcha_load_library()) {
    drupal_set_message(t('Error loading recaptchalib.'), 'error');
    return FALSE;
  }

  $form['recaptcha_site_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Site key'),
    '#default_value' => variable_get('recaptcha_site_key', ''),
    '#maxlength' => 40,
    '#description' => t('The site key given to you when you <a href="@url">register for reCAPTCHA</a>.', array('@url' => 'https://www.google.com/recaptcha/admin#createsite')),
    '#required' => TRUE,
  );
  $form['recaptcha_secret_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Secret key'),
    '#default_value' => variable_get('recaptcha_secret_key', ''),
    '#maxlength' => 40,
    '#description' => t('The secret key given to you when you <a href="@url">register for reCAPTCHA</a>.', array('@url' => 'https://www.google.com/recaptcha/admin#createsite')),
    '#required' => TRUE,
  );
  $form['recaptcha_noscript'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable fallback for browsers with JavaScript disabled'),
    '#default_value' => variable_get('recaptcha_noscript', 0),
    '#description' => t('If JavaScript is a requirement for your site, you should <strong>not</strong> enable this feature. Otherwise a compatibility layer will be added to the captcha to support non-js users.'),
  );

  $form['recaptcha_theme_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Theme settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['recaptcha_theme_settings']['recaptcha_theme'] = array(
    '#type' => 'select',
    '#title' => t('Theme'),
    '#description' => t('Defines which theme to use for reCAPTCHA.'),
    '#options' => array(
      'light' => t('Light'),
      'dark' => t('Dark'),
    ),
    '#default_value' => variable_get('recaptcha_theme', 'light'),
    '#required' => TRUE,
  );
  $form['recaptcha_theme_settings']['recaptcha_tabindex'] = array(
    '#type' => 'textfield',
    '#title' => t('Tabindex'),
    '#description' => t('Set the <a href="@tabindex">tabindex</a> of the widget and challenge. If other elements in your page use tabindex, it should be set to make user navigation easier.', array('@tabindex' => 'http://www.w3.org/TR/html4/interact/forms.html#adef-tabindex')),
    '#default_value' => variable_get('recaptcha_tabindex', ''),
    '#size' => 4,
  );

  return system_settings_form($form);
}

/**
 * Validation function for recaptcha_admin_settings().
 *
 * @see recaptcha_admin_settings()
 */
function recaptcha_admin_settings_validate($form, &$form_state) {
  $tabindex = $form_state['values']['recaptcha_tabindex'];
  if (!empty($tabindex) && !is_numeric($tabindex)) {
    form_set_error('recaptcha_tabindex', t('The tabindex must be an integer.'));
  }
}
